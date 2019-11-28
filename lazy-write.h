
#line 5 "index.md"

	#pragma once
	
#line 19 "index.md"

	
#line 70 "index.md"

	#include <memory>
	#include <fstream>
	#include <filesystem>
	#include <streambuf>
	namespace fs = std::filesystem;

#line 20 "index.md"
;
	class Lazy_Write {
			
#line 30 "index.md"


#line 1 "index.md"

		const std::string _path;
	
#line 130 "index.md"

	std::unique_ptr<std::ifstream>
		_reader;
	unsigned _count { 0 };
	std::unique_ptr<std::ofstream>
		_writer;

#line 22 "index.md"
;
		public:
			
#line 35 "index.md"


#line 1 "index.md"

		Lazy_Write(const std::string &p):
			_path { p }
		{
			
	_reader = std::move(
		std::make_unique<std::ifstream>(
			_path.c_str(), std::ios_base::binary | std::ios_base::in
		)
	);
;
		}
	
#line 86 "index.md"

	Lazy_Write &operator<<(
		const std::string &s
	) {
		for (const char c : s) {
			put(c);
		}
		return *this;
	}

#line 150 "index.md"

	Lazy_Write &put(char c) {
		
#line 159 "index.md"

	char got;
	if (_reader && _reader->get(got)) {
		if (got == c) {
			++_count;
			return *this;
		}
	}
	_reader = nullptr;

#line 172 "index.md"

	if (! _writer) {
		
#line 180 "index.md"

	_writer = std::move(
		std::make_unique<std::ofstream >(
			_path.c_str(),
			_count ? std::ios_base::binary | std::ios_base::in | std::ios_base::out : std::ios_base::binary | std::ios_base::out
		)
	);
	if (_count) {
		_writer->seekp(_count);
	}

#line 174 "index.md"
;
	}

#line 194 "index.md"

	if (_writer) {
		_writer->put(c);
		++_count;
	}

#line 152 "index.md"
;
		return *this;
	}

#line 203 "index.md"

	~Lazy_Write() {
		
#line 211 "index.md"

	_reader = nullptr;
	_writer = nullptr;
	fs::path p { _path };
	std::error_code err;
	auto got { fs::file_size(p, err) };

#line 221 "index.md"

	if (err) {
		std::ofstream empty {
			_path.c_str()
		};
		got = 0;
	}

#line 232 "index.md"

	if (got != _count) {
		fs::resize_file(p, _count, err);
	}

#line 205 "index.md"
;
	}

#line 24 "index.md"
;
	};

#line 7 "index.md"


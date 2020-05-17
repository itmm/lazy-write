
#line 5 "lazy.md"

	#pragma once
	
#line 19 "lazy.md"

	
#line 59 "lazy.md"

	#include <memory>
	#include <fstream>
	#include <filesystem>
	#include <streambuf>
	namespace fs = std::filesystem;

#line 20 "lazy.md"
;
	class Lazy_Write {
			
#line 30 "lazy.md"


#line 1 "lazy.md"

		const std::string _path;
	
#line 82 "lazy.md"

	std::unique_ptr<std::ifstream>
		_reader;
	unsigned _count { 0 };
	std::unique_ptr<std::ofstream>
		_writer;

#line 22 "lazy.md"
;
		public:
			
#line 35 "lazy.md"


#line 1 "lazy.md"

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
	
#line 69 "lazy.md"

	Lazy_Write &operator<<(
		const std::string &s
	) {
		for (const char c : s) {
			put(c);
		}
		return *this;
	}

#line 102 "lazy.md"

	Lazy_Write &put(char c) {
		
#line 111 "lazy.md"

	char got;
	if (_reader && _reader->get(got)) {
		if (got == c) {
			++_count;
			return *this;
		}
	}
	_reader = nullptr;

#line 124 "lazy.md"

	if (! _writer) {
		
#line 132 "lazy.md"

	_writer = std::move(
		std::make_unique<std::ofstream >(
			_path.c_str(),
			_count ? std::ios_base::binary | std::ios_base::in | std::ios_base::out : std::ios_base::binary | std::ios_base::out
		)
	);
	if (_count) {
		_writer->seekp(_count);
	}

#line 126 "lazy.md"
;
	}

#line 146 "lazy.md"

	if (_writer) {
		_writer->put(c);
		++_count;
	}

#line 104 "lazy.md"
;
		return *this;
	}

#line 155 "lazy.md"

	~Lazy_Write() {
		
#line 163 "lazy.md"

	_reader = nullptr;
	_writer = nullptr;
	fs::path p { _path };
	std::error_code err;
	auto got { fs::file_size(p, err) };

#line 173 "lazy.md"

	if (err) {
		std::ofstream empty {
			_path.c_str()
		};
		got = 0;
	}

#line 184 "lazy.md"

	if (got != _count) {
		fs::resize_file(p, _count, err);
	}

#line 157 "lazy.md"
;
	}

#line 24 "lazy.md"
;
	};

#line 7 "lazy.md"


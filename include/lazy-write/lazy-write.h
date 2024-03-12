#line 8 "README.md"
#pragma once
// globals
#line 25
// Lazy_Write prereqs
#line 53
#include <memory>
#include <fstream>
#include <filesystem>
#include <streambuf>
namespace fs = std::filesystem;
#line 26
class Lazy_Write {
		// privates
#line 74
		std::unique_ptr<std::ifstream> reader_;
		unsigned count_ { 0 };
		std::unique_ptr<std::ofstream> writer_;
#line 39
		const std::string path_;
#line 28
	public:
		// publics
#line 157
		~Lazy_Write() {
			// destruct
#line 166
			reader_ = nullptr;
			writer_ = nullptr;
			fs::path p { path_ };
			std::error_code err;
			auto got { fs::file_size(p, err) };
			// destruct 2
#line 178
			if (err) {
				std::ofstream empty {
					path_.c_str()
				};
				got = 0;
			}
			// destruct 3
#line 191
			if (got != count_) {
				fs::resize_file(p, count_, err);
			}
#line 159
		}
#line 93
		Lazy_Write &put(char c) {
			// put body
#line 103
			char got;
			if (reader_ && reader_->get(got)) {
				if (got == c) {
					++count_;
					return *this;
				}
			}
			reader_ = nullptr;
#line 119
			if (! writer_) {
				// init writer
#line 129
				writer_ = std::make_unique<std::ofstream >(
					path_.c_str(),
					count_ ?
						std::ios_base::binary |
							std::ios_base::in |
							std::ios_base::out :
						std::ios_base::binary |
							std::ios_base::out
				);
				if (count_) {
					writer_->seekp(count_);
				}
#line 121
			}
			// put body 2
#line 147
			if (writer_) {
				writer_->put(c);
				++count_;
			}
#line 95
			return *this;
		}
#line 64
		Lazy_Write &operator<<(const std::string &s) {
			for (const char c : s) { put(c); }
			return *this;
		}
#line 42
		Lazy_Write(const std::string &p):
			path_ { p }
		{
			// construct Lazy_Write
#line 83
			reader_ = std::make_unique<std::ifstream>(
				path_.c_str(),
				std::ios_base::binary | std::ios_base::in
			);
#line 46
		}
#line 30
};

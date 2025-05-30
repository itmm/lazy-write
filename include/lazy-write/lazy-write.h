#line 9 "README.md"
#pragma once
#line 25

#include <ostream>
#line 10
// globals
#line 29
// Lazy_Write prereqs
#line 57
#include <memory>
#include <fstream>
#include <filesystem>
#include <streambuf>
namespace fs = std::filesystem;
#line 30
class Lazy_Write: private std::streambuf, public std::ostream {
		// privates
#line 68
		std::unique_ptr<std::ifstream> reader_;
		unsigned count_ { 0 };
		std::unique_ptr<std::ofstream> writer_;
#line 43
		const std::string path_;
#line 87

		int overflow(int ch) override {
			// put body
#line 98
			char got;
			if (reader_ && reader_->get(got)) {
				if (got == ch) {
					++count_;
					return 0;
				}
			}
			reader_ = nullptr;
#line 114
			if (! writer_) {
				// init writer
#line 124
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
#line 116
			}
			// put body 2
#line 142
			if (writer_) {
				writer_->put(ch);
				++count_;
			}
#line 90
			return 0;
		}
#line 32
	public:
		// publics
#line 152
		~Lazy_Write() {
			// destruct
#line 161
			reader_ = nullptr;
			writer_ = nullptr;
			fs::path p { path_ };
			std::error_code err;
			auto got { fs::file_size(p, err) };
			// destruct 2
#line 173
			if (err) {
				std::ofstream empty {
					path_.c_str()
				};
				got = 0;
			}
			// destruct 3
#line 186
			if (got != count_) {
				fs::resize_file(p, count_, err);
			}
#line 154
		}
#line 46
		explicit Lazy_Write(const std::string &p):
			std::ostream { this }, path_ { p }
		{
			// construct Lazy_Write
#line 77
			reader_ = std::make_unique<std::ifstream>(
				path_.c_str(),
				std::ios_base::binary | std::ios_base::in
			);
#line 50
		}
#line 34
};

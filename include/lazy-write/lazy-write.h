#line 8 "README.md"
#pragma once
#line 24

#include <ostream>
#line 9
// globals
#line 28
// Lazy_Write prereqs
#line 54
#include <memory>
#include <fstream>
#include <filesystem>
#include <streambuf>
namespace fs = std::filesystem;
#line 29
class Lazy_Write: private std::streambuf, public std::ostream {
		// privates
#line 65
		std::unique_ptr<std::ifstream> reader_;
		unsigned count_ { 0 };
		std::unique_ptr<std::ofstream> writer_;
#line 42
		const std::string path_;
#line 84

		int overflow(int ch) override {
			// put body
#line 95
			char got;
			if (reader_ && reader_->get(got)) {
				if (got == ch) {
					++count_;
					return 0;
				}
			}
			reader_ = nullptr;
#line 111
			if (! writer_) {
				// init writer
#line 121
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
#line 113
			}
			// put body 2
#line 139
			if (writer_) {
				writer_->put(ch);
				++count_;
			}
#line 87
			return 0;
		}
#line 31
	public:
		// publics
#line 149
		~Lazy_Write() {
			// destruct
#line 158
			reader_ = nullptr;
			writer_ = nullptr;
			fs::path p { path_ };
			std::error_code err;
			auto got { fs::file_size(p, err) };
			// destruct 2
#line 170
			if (err) {
				std::ofstream empty {
					path_.c_str()
				};
				got = 0;
			}
			// destruct 3
#line 183
			if (got != count_) {
				fs::resize_file(p, count_, err);
			}
#line 151
		}
#line 45
		explicit Lazy_Write(const std::string &p): std::ostream { this }, path_ { p } {
			// construct Lazy_Write
#line 74
			reader_ = std::make_unique<std::ifstream>(
				path_.c_str(),
				std::ios_base::binary | std::ios_base::in
			);
#line 47
		}
#line 33
};

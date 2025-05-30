<!-- vim: set spelllang=en noexpandtab: -->
# Only write into a file if it is changing

* improves working with `make`

Header is written to `include/lazy-write/lazy-write.h`:

```c++
#pragma once
// globals
```

Implementation in `lazy-write.cpp` via `#define` in header:

```c++
#define lw_IMPL
#include "lazy-write/lazy-write.h"
```

Define class in `include/lazy-write/lazy-write.h`:

```c++
// ...
#pragma once

#include <ostream>
// ...
// globals
// Lazy_Write prereqs
class Lazy_Write: private std::streambuf, public std::ostream {
		// privates
	public:
		// publics
};
// ...
```

Add path:

```c++
// ...
		// privates
		const std::string path_;
// ...
		// publics
		explicit Lazy_Write(const std::string &p):
			std::ostream { this }, path_ { p }
		{
			// construct Lazy_Write
		}
// ...
```

```c++
// ...
// Lazy_Write prereqs
#include <memory>
#include <fstream>
#include <filesystem>
#include <streambuf>
namespace fs = std::filesystem;
// ...
```

```c++
// ...
		// privates
		std::unique_ptr<std::ifstream> reader_;
		unsigned count_ { 0 };
		std::unique_ptr<std::ofstream> writer_;
// ...
```

```c++
// ...
			// construct Lazy_Write
			reader_ = std::make_unique<std::ifstream>(
				path_.c_str(),
				std::ios_base::binary | std::ios_base::in
			);
// ...
```

```c++
// ...
		const std::string path_;

		int overflow(int ch) override {
			// put body
			return 0;
		}
// ...
```

```c++
// ...
			// put body
			char got;
			if (reader_ && reader_->get(got)) {
				if (got == ch) {
					++count_;
					return 0;
				}
			}
			reader_ = nullptr;
// ...
```

```c++
// ...
			// put body
			// ...
			reader_ = nullptr;
			if (! writer_) {
				// init writer
			}
			// put body 2
// ...
```

```c++
// ...
				// init writer
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
// ...
```

```c++
// ...
			// put body 2
			if (writer_) {
				writer_->put(ch);
				++count_;
			}
// ...
```

```c++
// ...
		// publics
		~Lazy_Write() {
			// destruct
		}
// ...
```

```c++
// ...
			// destruct
			reader_ = nullptr;
			writer_ = nullptr;
			fs::path p { path_ };
			std::error_code err;
			auto got { fs::file_size(p, err) };
			// destruct 2
// ...
```

```c++
// ...
			// destruct 2
			if (err) {
				std::ofstream empty {
					path_.c_str()
				};
				got = 0;
			}
			// destruct 3
// ...
```

```c++
// ...
			// destruct 3
			if (got != count_) {
				fs::resize_file(p, count_, err);
			}
// ...
```

Create unit-tests in `t_lazy-write.cpp`:

```c++
#include "lazy-write/lazy-write.h"
#include "solid/require.h"
// main prereqs
int main() {
	// unit-tests
}
```

```c++
// ...
// main prereqs
// unit-tests prereqs
// ...
```

```c++
// ...
// unit-tests prereqs
void lazy_write(fs::path path, const std::string &content) {
	std::string p { path.string() };
	{
		Lazy_Write lw { p };
		lw << content;
	}
	require(fs::file_size(path) == content.size());
	std::ifstream in { p };
	using it = std::istreambuf_iterator<char>;
	std::string got { it { in }, it { } };
	require(got == content);
}
// ...
```

```c++
// ...
	// unit-tests
	{ // test 1
		fs::path p { "a.tmp" };
		lazy_write(p, "");
		fs::remove(p);
	}
// ...
```

```c++
// ...
	// unit-tests
	{ // test 2
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		fs::remove(p);
	}
// ...
```

```c++
// ...
	// unit-tests
	{ // test 3
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "");
		fs::remove(p);
	}
// ...
```

```c++
// ...
	// unit-tests
	{ // test 4
		fs::path p { "a.tmp" };
		lazy_write(p, "");
		lazy_write(p, "abc");
		fs::remove(p);
	}
// ...
```

```c++
// ...
	// unit-tests
	{ // test 5
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "ab");
		fs::remove(p);
	}
// ...
```

```c++
// ...
	// unit-tests
	{ // test 6
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "ad");
		fs::remove(p);
	}
// ...
```

```c++
// ...
	// unit-tests
	{ // test 7
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "adef");
		fs::remove(p);
	}
// ...
```


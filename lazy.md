# Only write into a file if it is changing
* improves working with `make`

```
@Def(file: lazy-write.h)
	#pragma once
	@put(globals)
@End(file: lazy-write.h)
```

```
@Def(file: lazy-write.cpp)
	#define lw_IMPL
	#include "lazy-write.h"
@End(file: lazy-write.cpp)
```

```
@def(globals)
	@put(Lazy_Write prereqs);
	class Lazy_Write {
			@put(privates);
		public:
			@put(publics);
	};
@end(globals)
```

```
@def(privates)
@end(privates)
```

```
@def(publics)
@end(publics)
```

```
@def(construct @class())
	@add(privates)
		const std::string _path;
	@end(privates)
	@add(publics)
		Lazy_Write(const std::string &p):
			_path { p }
		{
			@put(construct);
		}
	@end(publics)
@end(construct @class())
```

```
@put(construct @class(Lazy_Write))
```

```
@def(Lazy_Write prereqs)
	#include <memory>
	#include <fstream>
	#include <filesystem>
	#include <streambuf>
	namespace fs = std::filesystem;
@end(Lazy_Write prereqs)
```

```
@add(publics)
	Lazy_Write &operator<<(
		const std::string &s
	) {
		for (const char c : s) {
			put(c);
		}
		return *this;
	}
@end(publics)
```

```
@add(privates)
	std::unique_ptr<std::ifstream>
		_reader;
	unsigned _count { 0 };
	std::unique_ptr<std::ofstream>
		_writer;
@end(privates)
```

```
@def(construct)
	_reader = std::move(
		std::make_unique<std::ifstream>(
			_path.c_str(), std::ios_base::binary | std::ios_base::in
		)
	);
@end(construct)
```

```
@add(publics)
	Lazy_Write &put(char c) {
		@put(put);
		return *this;
	}
@end(publics)
```

```
@def(put)
	char got;
	if (_reader && _reader->get(got)) {
		if (got == c) {
			++_count;
			return *this;
		}
	}
	_reader = nullptr;
@end(put)
```

```
@add(put)
	if (! _writer) {
		@put(init writer);
	}
@end(put)
```

```
@def(init writer)
	_writer = std::move(
		std::make_unique<std::ofstream >(
			_path.c_str(),
			_count ? std::ios_base::binary | std::ios_base::in | std::ios_base::out : std::ios_base::binary | std::ios_base::out
		)
	);
	if (_count) {
		_writer->seekp(_count);
	}
@end(init writer)
```

```
@add(put)
	if (_writer) {
		_writer->put(c);
		++_count;
	}
@end(put)
```

```
@add(publics)
	~Lazy_Write() {
		@put(destruct);
	}
@end(publics)
```

```
@def(destruct)
	_reader = nullptr;
	_writer = nullptr;
	fs::path p { _path };
	std::error_code err;
	auto got { fs::file_size(p, err) };
@end(destruct)
```

```
@add(destruct)
	if (err) {
		std::ofstream empty {
			_path.c_str()
		};
		got = 0;
	}
@end(destruct)
```

```
@add(destruct)
	if (got != _count) {
		fs::resize_file(p, _count, err);
	}
@end(destruct)
```


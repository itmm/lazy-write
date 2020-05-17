# Only write into a file if it is changing
* improves working with `make`

```
@inc(lazy.md)
```

```
@Def(file: main.cpp)
	#include "lazy-write.h"
	#include <cassert>
	@put(main prereqs);
	int main() {
		@put(unit-tests);
	}
@End(file: main.cpp)
```

```
@def(main prereqs)
	@put(unit-tests prereqs);
@end(main prereqs)
```

```
@def(unit-tests prereqs)
	void lazy_write(
		fs::path path,
		const std::string &content
	) {
		std::string p { path.string() };
		{
			Lazy_Write lw { p };
			lw << content;
		}
		assert(fs::file_size(path) ==
			content.size());
		std::ifstream in { p };
		using it = std::istreambuf_iterator<char>;
		std::string got {
			it { in }, it { }
		};
		assert(got == content);
	}
@end(unit-tests prereqs)
```

```
@def(unit-tests) {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	fs::remove(p);
} @end(unit-tests)
```

```
@add(unit-tests) {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	fs::remove(p);
} @end(unit-tests)
```

```
@add(unit-tests) {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "");
	fs::remove(p);
} @end(unit-tests)
```

```
@add(unit-tests) {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	lazy_write(p, "abc");
	fs::remove(p);
} @end(unit-tests)
```

```
@add(unit-tests) {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ab");
	fs::remove(p);
} @end(unit-tests)
```

```
@add(unit-tests) {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ad");
	fs::remove(p);
} @end(unit-tests)
```

```
@add(unit-tests) {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "adef");
	fs::remove(p);
} @end(unit-tests)
```


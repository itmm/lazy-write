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
@Def(file: main.cpp)
	#include "lazy-write.h"
	#include <cassert>
	int main() {
		@put(unit-tests);
	}
@End(file: main.cpp)
```

```
@def(unit-tests) {
	Lazy_Write lw { "a.tmp" };
} @end(unit-tests)
```

```
@def(Lazy_Write prereqs)
	#include <memory>
	#include <fstream>
@end(Lazy_Write prereqs)
```

```
@add(privates)
	std::unique_ptr<std::ifstream>
		_reader;
	std::unique_ptr<std::ofstream>
		_writer;
@end(privates)
```


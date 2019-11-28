
#line 59 "index.md"

	#include "lazy-write.h"
	#include <cassert>
	
#line 80 "index.md"

	
#line 99 "index.md"

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

#line 81 "index.md"
;

#line 62 "index.md"
;
	int main() {
		
#line 122 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	fs::remove(p);
} 
#line 240 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	fs::remove(p);
} 
#line 248 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "");
	fs::remove(p);
} 
#line 257 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	lazy_write(p, "abc");
	fs::remove(p);
} 
#line 266 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ab");
	fs::remove(p);
} 
#line 275 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ad");
	fs::remove(p);
} 
#line 284 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "adef");
	fs::remove(p);
} 
#line 64 "index.md"
;
	}

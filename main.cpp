
#line 9 "index.md"

	#include "lazy-write.h"
	#include <cassert>
	
#line 20 "index.md"

	
#line 26 "index.md"

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

#line 21 "index.md"
;

#line 12 "index.md"
;
	int main() {
		
#line 49 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	fs::remove(p);
} 
#line 57 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	fs::remove(p);
} 
#line 65 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "");
	fs::remove(p);
} 
#line 74 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	lazy_write(p, "abc");
	fs::remove(p);
} 
#line 83 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ab");
	fs::remove(p);
} 
#line 92 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ad");
	fs::remove(p);
} 
#line 101 "index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "adef");
	fs::remove(p);
} 
#line 14 "index.md"
;
	}

#line 200 "README.md"
#include "lazy-write/lazy-write.h"
#include "solid/require.h"
// main prereqs
#line 211
// unit-tests prereqs
#line 218
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
#line 203
int main() {
	// unit-tests
#line 306
	{ // test 7
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "adef");
		fs::remove(p);
	}
#line 294
	{ // test 6
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "ad");
		fs::remove(p);
	}
#line 282
	{ // test 5
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "ab");
		fs::remove(p);
	}
#line 270
	{ // test 4
		fs::path p { "a.tmp" };
		lazy_write(p, "");
		lazy_write(p, "abc");
		fs::remove(p);
	}
#line 258
	{ // test 3
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "");
		fs::remove(p);
	}
#line 247
	{ // test 2
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		fs::remove(p);
	}
#line 236
	{ // test 1
		fs::path p { "a.tmp" };
		lazy_write(p, "");
		fs::remove(p);
	}
#line 205
}

#line 198 "README.md"
#include "lazy-write/lazy-write.h"
#include "solid/require.h"
// main prereqs
#line 209
// unit-tests prereqs
#line 216
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
#line 201
int main() {
	// unit-tests
#line 304
	{ // test 7
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "adef");
		fs::remove(p);
	}
#line 292
	{ // test 6
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "ad");
		fs::remove(p);
	}
#line 280
	{ // test 5
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "ab");
		fs::remove(p);
	}
#line 268
	{ // test 4
		fs::path p { "a.tmp" };
		lazy_write(p, "");
		lazy_write(p, "abc");
		fs::remove(p);
	}
#line 256
	{ // test 3
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		lazy_write(p, "");
		fs::remove(p);
	}
#line 245
	{ // test 2
		fs::path p { "a.tmp" };
		lazy_write(p, "abc");
		fs::remove(p);
	}
#line 234
	{ // test 1
		fs::path p { "a.tmp" };
		lazy_write(p, "");
		fs::remove(p);
	}
#line 203
}

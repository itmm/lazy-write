
#line 5 "index.md"

	#pragma once
	
#line 19 "index.md"

	
#line 75 "index.md"

	#include <memory>
	#include <fstream>

#line 20 "index.md"
;
	class Lazy_Write {
			
#line 30 "index.md"


#line 1 "index.md"

		const std::string _path;
	
#line 82 "index.md"

	std::unique_ptr<std::ifstream>
		_reader;
	std::unique_ptr<std::ofstream>
		_writer;

#line 22 "index.md"
;
		public:
			
#line 35 "index.md"


#line 1 "index.md"

		Lazy_Write(const std::string &p):
			_path { p }
		{
			;
		}
	
#line 24 "index.md"
;
	};

#line 7 "index.md"


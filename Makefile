MDs = $(shell hx-srcs.sh)
GENs = $(shell hx-files.sh $(MDs))
CXXs = $(filter %.cpp, $(GENs))
OBJs = $(CXXs:.cpp=.o)

.PHONY: clean test

hx_run: $(MDs)
	@echo "HX"
	@hx
	@date >hx_run
	@make --no-print-directory test

test: lazy-write
	@echo "TEST"
	@./lazy-write

clean:
	@echo "RM"
	@rm -f hx_run lazy-write $(OBJs) $(GENs)

CXXFLAGS += -Wall -std=c++17

lazy-write: $(OBJs)
	@echo "LD $@"
	@$(CXX) $(CXXFLAGS) $^ -lstdc++fs -o $@

lazy-write.cpp: lazy-write.h
	@touch $@

main.cpp: lazy-write.h
	@touch $@

%.o: %.cpp
	@echo "  C++ $@"
	@$(CXX) $(CXXFLAGS) -c $^ -o $@

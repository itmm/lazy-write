MDs = $(shell hx-srcs.sh)
GENs = $(shell hx-files.sh $(MDs))
CXXs = $(filter %.cpp, $(GENs))
OBJs = $(CXXs:.cpp=.o)

.PHONY: clean test

hx_run: $(MDs)
	@echo "HX"
	@hx
	@make --no-print-directory test

test: lazy-write
	@echo "TEST"
	@./lazy-write

clean:
	@echo "RM"
	@rm -f lazy-write $(OBJs) $(GENs)

CXXFLAGS += -Wall -std=c++17

lazy-write: $(OBJs)
	@echo "LD $@"
	@$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	@echo "  C++ $@"
	@$(CXX) $(CXXFLAGS) -c $^ -o $@

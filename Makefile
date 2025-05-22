.PHONY: all tests clean solid-require

CXXFLAGS += -O3 -Wall -Wextra -Wpedantic -Werror -std=c++20 \
	-I./include -I./solid-require/include

T_APP = t_lazy-write
T_SOURCES = $(T_APP).cpp

LIB = liblazywrite.a
L_SOURCES = lazy-write.cpp
L_OBJECTS = $(L_SOURCES:.cpp=.o)
L_HEADER = include/lazy-write/lazy-write.h

LIBS = $(LIB) solid-require/librequire.a
LIBS_HEADER = solid-require/include/solid/require.h

MDP_RUN = mdp.run

all: $(MDP_RUN) solid-require
	@$(MAKE) --no-print-directory tests

solid-require:
	@echo building solid-require
	@$(MAKE) --no-print-directory -C solid-require

$(MDP_RUN): $(wildcard *.md)
	@echo extracting source code
	@[ -x "$$(command -v mdp)" ] || echo "mdp not installed" 1>&2
	@[ -x "$$(command -v mdp)" ] && mdp README.md
	@date >$@

%.o:%.cpp
	@echo "  buliding" $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

tests: $(T_APP)
	@echo running unit-tests
	@./$(T_APP)

$(T_APP): $(T_SOURCES) $(LIBS) $(LIBS_HEADER) $(T_HEADER) $(L_HEADER)
	@echo building $@
	@$(CXX) $(CXXFLAGS) $(T_SOURCES) $(LIBS) -o $@

$(LIB): $(L_OBJECTS) $(L_HEADER)
	@echo building $@
	@$(AR) -cr $@ $(L_OBJECTS)

clean:
	@echo remove temporaries
	@rm -f $(T_APP) $(MDP_RUN)
	@$(MAKE) --no-print-directory -C solid-require clean
	@[ -x "$$(command -v mdp)" ] && rm -f $(T_SOURCES) $(L_HEADER) \
		$(L_SOURCES) $(L_OBJECTS)

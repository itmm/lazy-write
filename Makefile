
.PHONY: test clean

CXXFLAGS += -Wall -std=c++20 -I./include -I./solid-require/include

APP = t_lazy-write
SOURCES = lazy-write.cpp $(APP).cpp
OTHER_SOURCES = solid-require/solid/require.cpp
HEADER = include/lazy-write/lazy-write.h
OTHER_HEADER = solid-require/include/solid/require.h
MDP_RUN = mdp.run

test: 
	$(MAKE) $(MDP_RUN)
	./$(APP)

mdp.run: README.md
	mdp $^ && date >$@ && $(MAKE) $(APP)

$(APP): $(SOURCES) $(OTHER_SOURCES) $(HEADER) $(OTHER_HEADER)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(OTHER_SOURCES) -o $@

clean:
	rm -f $(APP) $(MDP_RUN) $(SOURCES) $(HEADER)


CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++14 -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

tests_importance: bin/tests_importance

bin/tests_importance: obj/catch.o ./tests/tests_importance.cpp ./src/importance.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# .DEFAULT_GOAL := exec
.PHONY: clean tests_importance

clean:
	rm -rf ./bin/* ./obj/*
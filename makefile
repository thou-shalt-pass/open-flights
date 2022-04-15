CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++14 -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

tests_importance: bin/tests_importance

bin/tests_importance: ./tests/tests_importance.cpp ./src/importance.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# .DEFAULT_GOAL := exec
.PHONY: clean tests_importance

clean:
	rm -rf ./bin/*
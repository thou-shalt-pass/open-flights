CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++14 -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

tests_importance: bin/tests_importance
tests_data: bin/tests_data
main: bin/main

bin/main: ./src/data.cpp ./src/main.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@
bin/tests_importance: ./tests/tests_importance.cpp ./src/importance.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
bin/tests_data: ./tests/tests_data.cpp ./src/tests_data.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
# .DEFAULT_GOAL := exec
.PHONY: clean tests_importance

clean:
	rm -rf ./bin/*
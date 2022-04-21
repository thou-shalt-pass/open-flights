CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++14 -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

main: bin/main
tests_importance: bin/tests_importance
tests_matrix_operation: bin/tests_matrix_operation
tests_strongly_connected_components: bin/tests_strongly_connected_components

bin/main: ./src/data.cpp ./src/main.cpp ./src/strongly_connected_components.cpp ./src/importance.cpp ./src/matrix_operation.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_importance: reserve_obj/catch.o ./tests/tests_utilities.cpp ./tests/tests_importance.cpp ./src/importance.cpp ./src/matrix_operation.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_matrix_operation: reserve_obj/catch.o ./tests/tests_utilities.cpp ./tests/tests_matrix_operation.cpp ./src/matrix_operation.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_strongly_connected_components: reserve_obj/catch.o ./tests/tests_utilities.cpp ./tests/tests_strongly_connected_components.cpp ./src/strongly_connected_components.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

reserve_obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.DEFAULT_GOAL := main
.PHONY: clean main tests_importance tests_matrix_operation tests_strongly_connected_components

clean:
	rm -rf ./bin/* ./obj/*

clean_all:
	rm -rf ./bin/* ./obj/* ./reserve_obj/*

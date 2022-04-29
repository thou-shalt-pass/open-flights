CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++14 -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

main: bin/main
tests_importance: bin/tests_importance
tests_matrix_operation: bin/tests_matrix_operation
tests_strongly_connected_components: bin/tests_strongly_connected_components
tests_all_pairs_shortest_paths: bin/tests_all_pairs_shortest_paths
tests_dfs: bin/tests_dfs

bin/main: ./obj/data.o ./obj/main.o ./obj/strongly_connected_components.o ./obj/importance.o ./obj/all_pairs_shortest_paths.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_importance: ./reserve_obj/catch.o ./obj/tests_utilities.o ./obj/tests_importance.o ./obj/importance.o ./obj/data.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_matrix_operation: ./reserve_obj/catch.o ./obj/tests_utilities.o ./obj/tests_matrix_operation.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_strongly_connected_components: ./reserve_obj/catch.o ./obj/tests_utilities.o ./obj/tests_strongly_connected_components.o ./obj/strongly_connected_components.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_all_pairs_shortest_paths: ./reserve_obj/catch.o ./obj/tests_utilities.o ./obj/tests_all_pairs_shortest_paths.o ./obj/all_pairs_shortest_paths.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests_dfs: ./reserve_obj/catch.o ./obj/tests_utilities.o ./obj/tests_dfs.o
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/data.o: ./src/data.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/main.o: ./src/main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/importance.o: ./src/importance.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/strongly_connected_components.o: ./src/strongly_connected_components.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/all_pairs_shortest_paths.o: ./src/all_pairs_shortest_paths.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/tests_matrix_operation.o: ./tests/tests_matrix_operation.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/tests_importance.o: ./tests/tests_importance.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/tests_strongly_connected_components.o: ./tests/tests_strongly_connected_components.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/tests_all_pairs_shortest_paths.o: ./tests/tests_all_pairs_shortest_paths.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
  
obj/tests_dfs.o: ./tests/tests_dfs.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

obj/tests_utilities.o: tests/tests_utilities.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

reserve_obj/catch.o: tests/catch.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.DEFAULT_GOAL := main

.PHONY: clean main tests_importance tests_matrix_operation tests_strongly_connected_components tests_dfs tests_all_pairs_shortest_paths

clean:
	rm -rf ./bin/* ./obj/*

clean_all:
	rm -rf ./bin/* ./obj/* ./reserve_obj/*

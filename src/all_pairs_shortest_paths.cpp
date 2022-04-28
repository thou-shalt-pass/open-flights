// #include <iostream>
#include <stdexcept>

#include "all_pairs_shortest_paths.h"

/*
void Print2DVector(const Matrix<size_t>& vect){
    for(size_t i = 0; i < vect.size(); i++){
        for(size_t j = 0; j < vect.size(); j++){
            std::cout << vect[i][j] << " ";
        }      
        std::cout << std::endl;
    }  
    std::cout <<std::endl;
}

void Print2DVector(const Matrix<unsigned>& vect){
    for(size_t i = 0; i < vect.size(); i++){
        for(size_t j = 0; j < vect.size(); j++){
            std::cout << vect[i][j] << " ";
        }      
        std::cout << std::endl;
    }  
    std::cout <<std::endl;
}

void PrintVector(const std::vector<double> vect){
    for(size_t i = 0; i < vect.size(); i++){
        std::cout << vect[i] << " ";
    }
    std::cout <<std::endl;
}
*/

/**
 * @brief Check whether a graph is valid by checking all of its vectors has the same length
 * 
 * @param graph the adjacent matrix representation of the graph
 */
void isValid(const AdjMatrix& graph) {
    for (size_t i = 0; i < graph.size(); i++) {
        if (graph.size() != graph[i].size()) {
            throw std::runtime_error("Graph is not valid");
        }
    }
}

std::vector<size_t> PathReconstruction(const Matrix<size_t>& next, size_t start, size_t end) {
    if (next[start][end] == kNoAirline) { return std::vector<size_t>(); }

    std::vector<size_t> path;
    path.push_back(start);
    size_t current = start;
    while(current != end) {
        current = next[current][end];
        path.push_back(current);
    }

    return path;
}

Matrix<size_t> FloydWarshall(Matrix<unsigned>& distance) {
    size_t n = distance.size();
    Matrix<size_t> next(n, std::vector<size_t>(n, kNoAirline));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (distance[i][j] != kNoAirline) {
                next[i][j] = j;
            }
        }
    }

    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                // if (distance[i][k] != kNoAirline && distance[k][j] != kNoAirline) {
                    // By the definition of kNoAirline, this addition operation will not cause an overflow
                    unsigned new_distance = distance[i][k] + distance[k][j];
                    if (new_distance < distance[i][j]){
                        distance[i][j] = new_distance;
                        next[i][j] = next[i][k];
                    }
                // }
            }
        }
    }
    return next;
}

std::pair<Matrix<unsigned>, Matrix<size_t> > AllPairsShortestPaths(const AdjMatrix& graph) {
    // we can assume the graph is valid
    // isValid(graph);

    size_t n = graph.size();
    Matrix<unsigned> distance(n, std::vector<unsigned>(n));
    for(size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; j++) {
            distance[i][j] = graph[i][j].distance;
        }
    }
    Matrix<size_t> next = FloydWarshall(distance);
    return std::make_pair(std::move(distance), std::move(next));
}
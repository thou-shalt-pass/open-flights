#ifndef _ALL_PAIRS_SHORTEST_PATHS_H
#define _ALL_PAIRS_SHORTEST_PATHS_H

#include "type.h"
#include <iostream>

/**
 * @brief find all shortest path between all pairs of airports by using Floyd-Warshall
 * 
 * @param graph `graph[i][j]` is the distance between i and j, graph[i][i]'s value is kNoAirline
 * @return std::pair<Matrix<unsigned>, Matrix<size_t> > 
 * matrix1[i][j] is the shortest distance between i and j
 * matrix2[i][j] is the next vertex to go from vertex i to vertex j
 */
std::pair<Matrix<unsigned>, Matrix<size_t> > AllPairsShortestPaths(const AdjMatrix& graph);

/**
 * @brief 
 * 
 * @param distance 
 * @return Matrix<size_t> 
 */
Matrix<size_t> FloydWarshall(Matrix<unsigned>& distance);

/*
void Print2DVector(const Matrix<size_t>& vect);

void Print2DVector(const Matrix<unsigned>& vect);
*/

#endif
#ifndef _ALL_PAIRS_SHORTEST_PATHS_H
#define _ALL_PAIRS_SHORTEST_PATHS_H

#include "type.h"

/**
 * @brief find the shortest path between all pairs of airports by using Floyd-Warshall
 * 
 * @param graph `graph[i][j]` is the distance between i and j
 * @return `matrix[i][j].distance` is the shortest distance between i and j; 
 * `matrix[i][j].airports` is the vector contains the airports on the shortest path between i and j in order
 */
Matrix<Edge> AllPairsShortestPaths(const AdjMatrix& graph);

#endif
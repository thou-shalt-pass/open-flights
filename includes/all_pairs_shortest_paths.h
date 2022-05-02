#ifndef _ALL_PAIRS_SHORTEST_PATHS_H
#define _ALL_PAIRS_SHORTEST_PATHS_H

#include "type.h"

/**
 * @brief find all shortest path between all pairs of airports by using Floyd-Warshall
 * 
 * @param graph `graph[i][j]` is the distance between i and j, graph[i][i]'s value is kNoAirline
 * @return APSPResult 
 * result.distance[i][j] is the shortest distance between i and j
 * result.next[i][j] is the next vertex to go from vertex i to vertex j
 */
APSPResult AllPairsShortestPaths(const AdjMatrix& graph);

/**
 * @brief Reconstruct the path from start to end using Matrix next generated from AllPairsShortestPath
 * 
 * @param next start vertex
 * @param start end vertex
 * @param end path matrix generated from AllPairsShortestPath
 * @return std::vector<size_t> 
 */
std::vector<size_t> PathReconstruction(const Matrix<size_t>& next, size_t start, size_t end);

#endif
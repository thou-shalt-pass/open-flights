#ifndef _IMPORTANCE_H
#define _IMPORTANCE_H

#include "type.h"

/**
 * @brief find the importance value of each airport by using PageRank
 * 
 * @param graph `graph[i][j] == kNoAirline` if and only if there is no airline between i and j
 * @return `vector[i] < vector[j]` if and only if i is less important than j
 */
std::vector<int> Importance(const AdjMatrix& graph);

#endif
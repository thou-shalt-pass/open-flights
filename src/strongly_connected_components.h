#ifndef _STRONGLY_CONNECTED_COMPONENTS_H
#define _STRONGLY_CONNECTED_COMPONENTS_H

#include <list>
#include <vector>

#include "type.h"

/**
 * @brief find if passagers need to re-check-in for all combinations of path
 * 
 * @param graph `graph[i][j] == kNoAirline` if and only if there is no airline between i and j
 * @param re_check_in `re_check_in[i] == false` if and only if i does not require re-check-in
 * @return passagers arriving at i can fly to j without re-check-in if and only if 
 * i and j is contained in a same vector; 
 * list is a partition of airports
 */
std::list<std::vector<size_t> > StronglyConnectedComponents(const AdjMatrix& graph, std::vector<bool> re_check_in);

#endif
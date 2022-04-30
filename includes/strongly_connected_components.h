#ifndef _STRONGLY_CONNECTED_COMPONENTS
#define _STRONGLY_CONNECTED_COMPONENTS

#include <vector>

#include "type.h"

/**
 * @brief find strongly connected components
 * 
 * @param graph adjacency list of a directed graph
 * @return collection of sets where each set represents a strongly connect component 
 * and contains nodes in the strongly connect component 
 */
std::vector<std::vector<size_t> > StronglyConnectedComponents(const AdjList& graph);

#endif
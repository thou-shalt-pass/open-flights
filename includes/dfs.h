#ifndef _DFS_H
#define _DFS_H

#include "type.h"

/**
 * @brief abstract DFS operation
 * 
 * @param graph adjacency list
 * @param operation function object of the operation
 */
template <typename Op>
void DFS(const AdjList& graph, Op operation);

#endif
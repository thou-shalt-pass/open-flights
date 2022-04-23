#ifndef _IMPORTANCE_H
#define _IMPORTANCE_H

#include "type.h"

/**
 * @brief find the importance value of each airport by using PageRank
 * 
 * @param graph adjacency list of a simple, directed, strongly connected graph
 * @param iteration_times the number of iterations
 * @return `vector[i] < vector[j]` if and only if i is less important than j
 */
std::vector<double> ImportanceIteration(const AdjList& graph, unsigned interation_half);

/**
 * @brief find the importance value of each airport by using PageRank
 * 
 * @param graph adjacency matrix of a simple, directed, strongly connected graph
 * @return `vector[i] < vector[j]` if and only if i is less important than j
 */
std::vector<double> ImportanceEigenvector(const AdjList& graph);

#endif
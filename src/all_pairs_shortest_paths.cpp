#include "all_pairs_shortest_paths.h"

/**
 * @brief Reconstruct the path from start to end using Matrix next generated from AllPairsShortestPath
 * 
 * @param next start vertex
 * @param start end vertex
 * @param end path matrix generated from AllPairsShortestPath
 * @return std::vector<size_t> 
 */
std::vector<size_t> PathReconstruction(const Matrix<size_t>& next, size_t start, size_t end) {
    if (next[start][end] == kNoAirline) { return std::vector<size_t>(); }

    std::vector<size_t> path;
    path.push_back(start);
    size_t current = start;
    while (current != end) {
        current = next[current][end];
        path.push_back(current);
    }

    return path;
}

/**
 * @brief Floyd-Warshall
 * 
 * @param distance in-para and out-para
 * @return Matrix<size_t> 
 */
Matrix<size_t> FloydWarshall(Matrix<unsigned>& distance) {
    size_t n = distance.size();
    Matrix<size_t> next(n, std::vector<size_t>(n, kNoAirline));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (distance[i][j] != kNoAirline) {
                next[i][j] = j;
            }
        }
    }

    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                // By the definition of kNoAirline, this addition operation will not cause an overflow
                unsigned new_distance = distance[i][k] + distance[k][j];
                if (new_distance < distance[i][j]){
                    distance[i][j] = new_distance;
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    return next;
}

/**
 * @brief find all shortest path between all pairs of airports by using Floyd-Warshall
 * 
 * @param graph `graph[i][j]` is the distance between i and j, graph[i][i]'s value is kNoAirline
 * @return APSPResult 
 * result.distance[i][j] is the shortest distance between i and j
 * result.next[i][j] is the next vertex to go from vertex i to vertex j
 */
APSPResult AllPairsShortestPaths(const AdjMatrix& graph) {
    size_t n = graph.size();
    Matrix<unsigned> distance(n, std::vector<unsigned>(n));
    for(size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i == j) {
                distance[i][j] = 0;
            } else {
                distance[i][j] = graph[i][j].distance;
            }
        }
    }
    Matrix<size_t> next = FloydWarshall(distance);
    return APSPResult(std::move(distance), std::move(next));
}

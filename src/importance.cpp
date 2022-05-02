#include "importance.h"
#include "matrix_operation.h"

/**
 * @brief helper for importance by interation
 * 
 * @param graph adjacency list of a simple, directed, strongly connected graph
 * @param curr_importance old PageRank vector
 * @param next_importance new PageRank vector (out-para)
 */
void PageRank(const AdjList& graph, const std::vector<double>& curr_importance, 
    std::vector<double>& next_importance) {
    next_importance.clear();
    next_importance.resize(graph.size(), 0);
    for (size_t u = 0; u < graph.size(); ++u) {
        double out_importance = curr_importance[u] / graph[u].size();
        for (size_t v : graph[u]) {
            next_importance[v] += out_importance;
        }
    }
}

/**
 * @brief find the importance value of each airport by using PageRank
 * 
 * @param graph adjacency list of a simple, directed, strongly connected graph
 * @param iteration_times the number of iterations
 * @return `vector[i] < vector[j]` if and only if i is less important than j
 */
std::vector<double> ImportanceIteration(const AdjList& graph, unsigned iteration_times) {
    double init_importance = static_cast<double>(1) / graph.size();
    std::vector<double> importance_1(graph.size(), init_importance), importance_2;
    unsigned iteration_times_half = iteration_times >> 1;
    for (unsigned i = 0; i < iteration_times_half; ++i) {
        PageRank(graph, importance_1, importance_2);
        PageRank(graph, importance_2, importance_1);
    }
    if (iteration_times & 1) {
        PageRank(graph, importance_1, importance_2);
        return importance_2;
    }
    return importance_1;
}

/**
 * @brief make a markov matrix
 * 
 * @param graph adjacency list of a simple, directed, strongly connected graph
 * @return Matrix<double> 
 */
Matrix<double> Normalize(const AdjList& graph) {
    size_t n = graph.size();
    Matrix<double> result(n, std::vector<double>(n, 0));
    for (size_t u = 0; u < n; ++u) {
        if (graph[u].size() > 0) {
            double d = 1.0 / graph[u].size();
            for (size_t v : graph[u]) {
                result[v][u] = d;
            }
        }
    }
    return result;
}

/**
 * @brief find the importance value of each airport
 * 
 * @param graph adjacency list of a simple, directed, strongly connected graph
 * @return `vector[i] < vector[j]` if and only if i is less important than j
 */
std::vector<double> ImportanceEigenvectorByLU(const AdjList& graph) {
    Matrix<double> matrix = Normalize(graph);
    for (size_t i = 0; i < graph.size(); ++i) {
        --matrix[i][i];
    }
    return FindOneDimNullSpaceByLU(matrix);
}

/**
 * @brief find the importance value of each airport
 * 
 * @param graph adjacency list of a simple, directed, strongly connected graph
 * @return `vector[i] < vector[j]` if and only if i is less important than j
 */
std::vector<double> ImportanceEigenvectorByGaussian(const AdjList& graph) {
    Matrix<double> matrix = Normalize(graph);
    for (size_t i = 0; i < graph.size(); ++i) {
        --matrix[i][i];
    }
    return FindOneDimNullSpaceByGaussian(matrix);
}
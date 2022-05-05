#ifndef _TYPE_H
#define _TYPE_H

#include <limits>
#include <list>
#include <string>
#include <vector>

/**
 * @brief 2D vector
 * 
 * @tparam T data type
 */
template <typename T>
using Matrix = std::vector<std::vector<T> >;

constexpr unsigned kNoAirline = (std::numeric_limits<unsigned>::max() >> 1) - 100000;

/**
 * @brief edge info represents airline
 * 
 */
struct Edge {
	unsigned distance;

	Edge() {}
	Edge(unsigned distance) : distance(distance) {}
};

/**
 * @brief node info represents airport
 * 
 */
struct Node{
	std::string city;
	std::string airport_name;
	std::string iata_code;
	double longitude;
	double latitude;

	Node() {}
	Node(std::string&& city, std::string&& airport_name, std::string&& iata_code, 
		double longitude, double latitude) 
		: city(std::forward<std::string>(city)), 
		airport_name(std::forward<std::string>(airport_name)), 
		iata_code(std::forward<std::string>(iata_code)), 
		longitude(longitude), latitude(latitude) {}
};

using AdjList = std::vector<std::list<size_t> >;
using AdjMatrix = Matrix<Edge>;

/**
 * @brief strongly connected components result wrapper
 * 
 */
struct SCCResult {
    // collection of sets (should in the order of decreasing size of sets)
    std::vector<std::vector<size_t> > collection;
    // maps node idx to scc idx
    std::vector<size_t> node_idx_to_scc_idx;
};

/**
 * @brief importance alogorithms result wrapper
 * 
 */
struct ImportanceIntegrationResult {
    std::vector<size_t> order_to_idx;// order -> node_idx
    std::vector<size_t> idx_to_order;// node_idx -> order
    std::vector<double> idx_to_imp_it;// node_idx -> importance result by iteration
    std::vector<double> idx_to_imp_lu;// node_idx -> importance result by LU decomposition
    std::vector<double> idx_to_imp_gaussian;// node_idx -> importance result by Gaussian elimination

    ImportanceIntegrationResult(size_t n) : order_to_idx(n), idx_to_order(n), idx_to_imp_it(n), idx_to_imp_lu(n), idx_to_imp_gaussian(n) {}

    void Set(size_t order, size_t idx, double imp_it, double imp_lu, double imp_gaussian) {
        order_to_idx[order] = idx;
        idx_to_order[idx] = order;
        idx_to_imp_it[idx] = imp_it;
        idx_to_imp_lu[idx] = imp_lu;
        idx_to_imp_gaussian[idx] = imp_gaussian;
    }
};

/**
 * @brief all pairs shortest path result wrapper
 * 
 */
struct APSPResult {
    Matrix<unsigned> distance;
    Matrix<size_t> next;
    
    APSPResult(size_t n) : distance(n, std::vector<unsigned>(n)), next(n, std::vector<size_t>(n)) {}
    APSPResult(Matrix<unsigned>&& distance, Matrix<size_t>&& next) 
		: distance(std::forward<Matrix<unsigned> >(distance)), next(std::forward<Matrix<size_t> >(next)) {}
};

#endif
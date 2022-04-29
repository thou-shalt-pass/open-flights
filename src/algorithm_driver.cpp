#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>

#include "all_pairs_shortest_paths.h"
#include "data.h"
#include "importance.h"
#include "strongly_connected_components.h"

template <typename T>
void VectorOutput(const std::vector<T>& vector, std::ostream& os) {
    size_t n = vector.size();
    for (size_t i = 0; i < n - 1; ++i) {
        os << vector[i] << ',';
    }
    os << vector[n - 1] << '\n';
}

template <typename T>
void MatrixOutput(const Matrix<T>& matrix, std::ostream& os) {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i) {
        VectorOutput(matrix[i], os);
    }
}

void ImportanceOutput(const Data& data, const std::vector<double>& pagerank_vec, std::ostream& os) {
    size_t n = pagerank_vec.size();
    // os << "PageRank vector sum: " << std::accumulate(pagerank_vec.begin(), pagerank_vec.end(), 0.0) << "\n\n";
    std::vector<std::pair<double, size_t> > vec_pair;// [importance, idx]
    vec_pair.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        vec_pair.emplace_back(pagerank_vec[i], i);
    }
    std::sort(vec_pair.begin(), vec_pair.end(), 
        [](const std::pair<double, size_t>& a, const std::pair<double, size_t>& b) { return a.first > b.first; });
    for (size_t i = 0; i < n; ++i) {
        double imp = vec_pair[i].first;
        size_t v = vec_pair[i].second;
        const Node& node = data.GetNode(v);
        os << imp << ',' << v << '\n';
        // os << imp << ',' << v << ',' << node.iata_code << ',' << node.city << ',' << node.airport_name << ','
        //     << node.longitude << ',' << node.latitude << '\n';
        // printf("#%2s: %.10s | %5s | %-20s | %3s\n", "Order", "Importance", "Node Index", "City", "IATA Code");
        // printf("#%2d: %.10f | %5d | %-20s | %3s\n", 
        //     (int)i + 1, imp, (int)v, data.GetNode(v).city.c_str(), 
        //     data.GetNode(v).iata_code.c_str());
    }
}

int main() {
    std::string input_filename_airport("data/airport_ori.csv"), input_filename_airline("data/route_ori.csv"), 
        output_filename_airport_largest_scc("result/airport_largest_scc.csv"), 
        output_filename_airline_largest_scc("result/airline_largest_scc.csv"), 
        output_filename_importance_it("result/importance_by_iteration.csv"), 
        output_filename_importance_lu("result/importance_by_lu_decomposition.csv"), 
        output_filename_importance_gaussian("result/importance_by_gaussian_elimination.csv"), 
        output_filename_apsp_distance("result/apsp_distance.csv"), 
        output_filename_apsp_next("result/apsp_next.csv"), 
        output_mkdir_cmd("mkdir result"), 
        output_zip_cmd("tar -zcvf result.tar.gz result");

    system(output_mkdir_cmd.c_str());
    
    std::ifstream airport_ori_ifs(input_filename_airport), airline_ori_ifs(input_filename_airline);
    Data data_ori(airport_ori_ifs, airline_ori_ifs);
    airport_ori_ifs.close();
    airline_ori_ifs.close();
    
    // find strongly connect components

    std::list<std::list<size_t> > scc = StronglyConnectedComponents(data_ori.GetAdjList());
    std::list<size_t> *largest_scc;
    size_t largest_scc_size = 0;
    for (std::list<size_t>& x : scc) {
        if (x.size() > largest_scc_size) {
            largest_scc_size = x.size();
            largest_scc = &x;
        }
    }

    std::unordered_set<std::string> largest_scc_set;
    for (size_t v : *largest_scc) {
        largest_scc_set.insert(data_ori.GetNode(v).iata_code);
    }

    std::ifstream airport_is_filter(input_filename_airport), airline_is_filter(input_filename_airline);
    std::ofstream airport_os_filter(output_filename_airport_largest_scc), airline_os_filter(output_filename_airline_largest_scc);

    FilterAirports(airport_os_filter, airport_is_filter, largest_scc_set);
    FilterAirlines(airline_os_filter, airline_is_filter, largest_scc_set);

    airport_is_filter.close();
    airline_is_filter.close();
    airport_os_filter.close();
    airline_os_filter.close();

    std::ifstream airport_scc_ifs(output_filename_airport_largest_scc), airline_scc_ifs(output_filename_airline_largest_scc);
    Data data_scc(airport_scc_ifs, airline_scc_ifs);
    airport_scc_ifs.close();
    airline_scc_ifs.close();

    // importance

    std::vector<double> importance_it = ImportanceIteration(data_scc.GetAdjList(), 5000);
    std::ofstream importance_it_ofs(output_filename_importance_it);
    ImportanceOutput(data_scc, importance_it, importance_it_ofs);
    importance_it_ofs.close();
    
    std::vector<double> importance_lu = ImportanceEigenvectorByLU(data_scc.GetAdjList());
    std::ofstream importance_lu_ofs(output_filename_importance_lu);
    ImportanceOutput(data_scc, importance_lu, importance_lu_ofs);
    importance_lu_ofs.close();

    std::vector<double> importance_gaussian = ImportanceEigenvectorByGaussian(data_scc.GetAdjList());
    std::ofstream importance_gaussian_ofs(output_filename_importance_gaussian);
    ImportanceOutput(data_scc, importance_gaussian, importance_gaussian_ofs);
    importance_gaussian_ofs.close();

    // all pairs shortest path
    
    Matrix<unsigned> apsp_distance;
    Matrix<size_t> apsp_next;
    std::tie(apsp_distance, apsp_next) = AllPairsShortestPaths(data_ori.GetAdjMatrix());
    std::ofstream apsp_distance_ofs(output_filename_apsp_distance), apsp_next_ofs(output_filename_apsp_next);
    MatrixOutput(apsp_distance, apsp_distance_ofs);
    MatrixOutput(apsp_next, apsp_next_ofs);
    apsp_distance_ofs.close();
    apsp_next_ofs.close();

    system(output_zip_cmd.c_str());
    
    return 0;
}

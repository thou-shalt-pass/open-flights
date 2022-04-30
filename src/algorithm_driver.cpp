#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

#include "all_pairs_shortest_paths.h"
#include "data.h"
#include "importance.h"
#include "strongly_connected_components.h"

template <typename InputIt>
void VectorOutput(InputIt begin, InputIt end, std::ostream& os) {
    if (begin == end) { return; }
    os << *begin;
    ++begin;
    while (begin != end) {
        os << ',' << *begin;
        ++begin;
    }
    os << '\n';
}

template <typename InputIt>
void MatrixOutput(InputIt begin, InputIt end, std::ostream& os) {
    while (begin != end) {
        VectorOutput(begin->cbegin(), begin->cend(), os);
        ++begin;
    }
}

void ImportanceOutput(const std::vector<double>& pagerank_vec, std::ostream& os) {
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
        os << imp << ',' << v << '\n';
    }
}

int main() {
    std::string input_filename_airport("data/airport_ori.csv"), input_filename_airline("data/route_ori.csv"), 
        output_filename_scc("result/scc.csv"), 
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

    std::vector<std::vector<size_t> > scc = StronglyConnectedComponents(data_ori.GetAdjList());
    std::sort(scc.begin(), scc.end(), [](const std::vector<size_t>& a, const std::vector<size_t>& b) {
        return a.size() > b.size();
    });

    std::ofstream scc_os(output_filename_scc);
    MatrixOutput(scc.cbegin(), scc.cend(), scc_os);
    scc_os.close();

    std::unordered_set<std::string> largest_scc_set;
    for (size_t v : scc.front()) {
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
    ImportanceOutput(importance_it, importance_it_ofs);
    importance_it_ofs.close();
    
    std::vector<double> importance_lu = ImportanceEigenvectorByLU(data_scc.GetAdjList());
    std::ofstream importance_lu_ofs(output_filename_importance_lu);
    ImportanceOutput(importance_lu, importance_lu_ofs);
    importance_lu_ofs.close();

    std::vector<double> importance_gaussian = ImportanceEigenvectorByGaussian(data_scc.GetAdjList());
    std::ofstream importance_gaussian_ofs(output_filename_importance_gaussian);
    ImportanceOutput(importance_gaussian, importance_gaussian_ofs);
    importance_gaussian_ofs.close();

    // all pairs shortest path
    
    APSPResult apsp_result = AllPairsShortestPaths(data_ori.GetAdjMatrix());
    std::ofstream apsp_distance_ofs(output_filename_apsp_distance), apsp_next_ofs(output_filename_apsp_next);
    MatrixOutput(apsp_result.distance.cbegin(), apsp_result.distance.cend(), apsp_distance_ofs);
    MatrixOutput(apsp_result.next.cbegin(), apsp_result.next.cend(), apsp_next_ofs);
    apsp_distance_ofs.close();
    apsp_next_ofs.close();

    system(output_zip_cmd.c_str());
    
    return 0;
}

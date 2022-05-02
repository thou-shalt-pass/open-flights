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

#include "filename_def.h"

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
void Vector2DOutput(InputIt begin, InputIt end, std::ostream& os) {
    while (begin != end) {
        VectorOutput(begin->cbegin(), begin->cend(), os);
        ++begin;
    }
}

template <typename InputIt>
void Vector2DOutput(InputIt begin, InputIt end, const std::string& result_filename) {
    std::ofstream ofs(result_filename);
    Vector2DOutput(begin, end, ofs);
    ofs.close();
}

void WriteSCCResult(const std::vector<std::vector<size_t> >& scc_collection, 
        const std::string& scc_result_filename) {
    std::ofstream ofs(scc_result_filename);
    Vector2DOutput(scc_collection.cbegin(), scc_collection.cend(), ofs);
    ofs.close();
}

void ImportanceOutput(const std::vector<double>& pagerank_vec, std::ostream& os) {
    size_t n = pagerank_vec.size();
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

void WriteImportanceResult(const std::vector<double>& pagerank_vec, 
        const std::string& importance_result_filename) {
    std::ofstream ofs(importance_result_filename);
    ImportanceOutput(pagerank_vec, ofs);
    ofs.close();
}

int main(int argc, char *argv[]) {
    int ret;
    char buf[128];

    std::cout << "---------------------------------------\n";
    std::cout << " CS 225 Final Project: OpenFlights\n";
    std::cout << " Team Members: tluo9-yanzhen4-yirongc3\n";
    std::cout << " Algorithm Driver\n";
    std::cout << "---------------------------------------\n";

    // make result directory
    system("mkdir result > /dev/null 2>&1");
    
    // store dataset to result
    const char *airport_data_filename, *airline_data_filename;
    if (argc == 1) {
        airport_data_filename = kFilenameInputDataAirportDefault;
        airline_data_filename = kFilenameInputDataAirlineDefault;
    } else if (argc == 2) {
        airport_data_filename = argv[1];
        airline_data_filename = kFilenameInputDataAirlineDefault;
    } else {
        airport_data_filename = argv[1];
        airline_data_filename = argv[2];
    }
    std::cout << "You are using airport and airline dataset: " << airport_data_filename << ", " << airline_data_filename << '\n';
    snprintf(buf, sizeof(buf), "cp %s %s", airport_data_filename, kFilenameResultInputDataAirport);
    ret = system(buf);
    if (ret != 0) {
        return ret;
    }
    snprintf(buf, sizeof(buf), "cp %s %s", airline_data_filename, kFilenameResultInputDataAirline);
    ret = system(buf);
    if (ret != 0) {
        return ret;
    }

    // read data
    Data data_ori = ReadData(kFilenameResultInputDataAirport, kFilenameResultInputDataAirline);

    // find strongly connect components
    std::vector<std::vector<size_t> > scc_collection = StronglyConnectedComponents(data_ori.GetAdjList());
    std::sort(scc_collection.begin(), scc_collection.end(), [](const std::vector<size_t>& a, const std::vector<size_t>& b) {
        return a.size() > b.size();
    });
    WriteSCCResult(scc_collection, kFilenameResultSCC);

    // importance
    Data data_largest_scc(data_ori, scc_collection[0]);
    std::vector<double> importance_it = ImportanceIteration(data_largest_scc.GetAdjList(), 5000);
    WriteImportanceResult(importance_it, kFilenameResultImportanceIt);
    std::vector<double> importance_lu = ImportanceEigenvectorByLU(data_largest_scc.GetAdjList());
    WriteImportanceResult(importance_lu, kFilenameResultImportanceLU);
    std::vector<double> importance_gaussian = ImportanceEigenvectorByGaussian(data_largest_scc.GetAdjList());
    WriteImportanceResult(importance_gaussian, kFilenameResultImportanceGaussian);

    // all pairs shortest path
    APSPResult apsp_result = AllPairsShortestPaths(data_ori.GetAdjMatrix());
    Vector2DOutput(apsp_result.distance.cbegin(), apsp_result.distance.cend(), kFilenameResultAPSPDistance);
    Vector2DOutput(apsp_result.next.cbegin(), apsp_result.next.cend(), kFilenameResultAPSPNext);

    // zip result
    snprintf(buf, sizeof(buf), "tar -zcvf %s result > /dev/null", kFilenameResultPackageDefault);
    system(buf);
    
    return 0;
}

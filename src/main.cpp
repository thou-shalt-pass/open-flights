#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>

#include "all_pairs_shortest_paths.h"
#include "data.h"
#include "importance.h"
#include "strongly_connected_components.h"

int main() {
    std::ifstream airport_is("data/airport_scc.csv"), airline_is("data/route_scc.csv");
    Data data(airport_is, airline_is);
    const AdjList& adj_list = data.GetAdjList();
    const AdjMatrix& adj_matrix = data.GetAdjMatrix();

    auto importance_output = [&data](const std::vector<double>& pagerank_vec) {
        std::cout << "sum: " << std::accumulate(pagerank_vec.begin(), pagerank_vec.end(), 0.0) << "\n\n";
        
        std::priority_queue<std::pair<double, size_t> > pq;
        for (size_t v = 0; v < pagerank_vec.size(); ++v) {
            pq.emplace(pagerank_vec[v], v);
        }

        for (size_t i = 0; i < 50; ++i) {
            double imp = pq.top().first;
            size_t v = pq.top().second;
            printf("#%2d: %.10f | %5d | %-18s | %3s\n", 
                (int)i + 1, imp, (int)v, data.GetNode(v).city.c_str(), 
                data.GetNode(v).iata_code.c_str());
            pq.pop();
        }
    };

    // std::list<std::list<size_t> > scc = StronglyConnectedComponents(adj_list);
    // std::list<size_t>* largest_scc;
    // size_t largest_scc_size = 0;
    // for (std::list<size_t>& x : scc) {
    //     if (x.size() > largest_scc_size) {
    //         largest_scc_size = x.size();
    //         largest_scc = &x;
    //     }
    // }

    // std::unordered_set<std::string> set;
    // for (size_t v : *largest_scc) {
    //     set.insert(data.GetNode(v).iata_code);
    // }

    // FilterAirports(std::cout, std::cin, set);
    // FilterAirlines(std::cout, std::cin, set);

    // Matrix<unsigned> apsp_distance;
    // Matrix<size_t> apsp_next;
    // std::tie(apsp_distance, apsp_next) = AllPairsShortestPaths(adj_matrix);

    // printf("---------------------------------\n");

    // std::vector<double> importance_it = ImportanceIteration(adj_list, 5000);
    // importance_output(importance_it);
    
    // printf("---------------------------------\n");

    // std::vector<double> importance_lu = ImportanceEigenvectorByLU(adj_list);
    // importance_output(importance_lu);

    // printf("---------------------------------\n");

    std::vector<double> importance_gaussian = ImportanceEigenvectorByGaussian(adj_list);
    importance_output(importance_gaussian);

    // printf("---------------------------------\n");

    // std::priority_queue<std::pair<double, size_t> > pq;
    // for (size_t v = 0; v < importance_it_pagerank_vec2.size(); ++v) {
    //     pq.emplace(importance_it_pagerank_vec2[v], v);
    // }

    // std::unordered_set<std::string> allowed_codes;
    // for (size_t i = 0; i < 3; ++i) {
    //     double imp = pq.top().first;
    //     size_t v = pq.top().second;
    //     allowed_codes.insert(data.GetNode(v).iata_code);
    //     pq.pop();
    // }
    // std::ofstream airport_ofs("./data/airport_scc_top3.csv"), 
    //     airline_ofs("./data/route_scc_top3.csv");
    // std::ifstream airport_ifs("./data/airport_scc.csv"), 
    //     airline_ifs("./data/route_scc.csv");

    // FilterAirports(airport_ofs, airport_ifs, allowed_codes);
    // FilterAirlines(airline_ofs, airline_ifs, allowed_codes);

    airport_is.close();
    airline_is.close();

    return 0;
}

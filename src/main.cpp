#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>

#include "all_pairs_shortest_paths.h"
#include "data.h"
#include "importance.h"
#include "strongly_connected_components.h"

int main() {
    Data data("data/airport_scc.csv", "data/route_scc.csv");
    const AdjList& adj_list = data.GetAdjList();
    const AdjMatrix& adj_matrix = data.GetAdjMatrix();

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

    Matrix<unsigned> apsp_distance;
    Matrix<size_t> apsp_next;
    std::tie(apsp_distance, apsp_next) = AllPairsShortestPaths(adj_matrix);

    printf("---------------------------------\n");

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

    std::vector<double> importance_it_pagerank_vec = ImportanceIteration(adj_list, 10);
    importance_output(importance_it_pagerank_vec);
    
    printf("---------------------------------\n");

    std::vector<double> importance_eig_pagerank_vec = ImportanceEigenvector(adj_list);
    importance_output(importance_eig_pagerank_vec);

    printf("---------------------------------\n");
    
    return 0;
}

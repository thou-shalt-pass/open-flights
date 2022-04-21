#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>

#include "data.h"
#include "importance.h"
#include "strongly_connected_components.h"

int main() {
    Data data("data/airport_scc.csv", "data/route_scc.csv");
    const AdjList& adj_list = data.GetAdjList();

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

    {
        std::vector<double> importance = ImportanceIteration(adj_list, 10);
        std::cout << "sum: " << std::accumulate(importance.begin(), importance.end(), 0.0) << "\n\n";
        
        std::priority_queue<std::pair<double, size_t> > pq;
        for (size_t v = 0; v < importance.size(); ++v) {
            pq.emplace(importance[v], v);
        }

        for (size_t i = 0; i < 50; ++i) {
            double imp = pq.top().first;
            size_t v = pq.top().second;
            printf("#%2d: %.10f | %5d | %-18s | %3s\n", 
                (int)i + 1, imp, (int)v, data.GetNode(v).city.c_str(), 
                data.GetNode(v).iata_code.c_str());
            pq.pop();
        }
    }

    printf("---------------------------------");

    {
        std::vector<double> importance = ImportanceEigenvector(adj_list);
        std::cout << "sum: " << std::accumulate(importance.begin(), importance.end(), 0.0) << "\n\n";
        
        std::priority_queue<std::pair<double, size_t> > pq;
        for (size_t v = 0; v < importance.size(); ++v) {
            pq.emplace(importance[v], v);
        }

        for (size_t i = 0; i < 50; ++i) {
            double imp = pq.top().first;
            size_t v = pq.top().second;
            printf("#%2d: %.10f | %5d | %-18s | %3s\n", 
                (int)i + 1, imp, (int)v, data.GetNode(v).city.c_str(), 
                data.GetNode(v).iata_code.c_str());
            pq.pop();
        }
    }
    
    return 0;
}

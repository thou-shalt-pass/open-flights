#include <iostream>
#include <numeric>

#include "data.h"
#include "importance.h"
#include "strongly_connected_components.h"

int main() {
    Data data("data/airport.csv", "data/route.csv");
    const AdjList& adj_list = data.GetAdjList();

    std::list<std::list<size_t> > scc = StronglyConnectedComponents(adj_list);
    // std::list<size_t>* largest_scc;
    // size_t largest_scc_size = 0;
    // for (std::list<size_t>& x : scc) {
    //     if (x.size() > largest_scc_size) {
    //         largest_scc_size = x.size();
    //         largest_scc = &x;
    //     }
    // }

    std::vector<double> importance = Importance(adj_list, 1);
    // std::cout << std::accumulate(importance.begin(), importance.end(), 0.0) << std::endl;

    return 0;
}

#include <queue>

#include "dfs.h"
#include "strongly_connected_components.h"

AdjList Transpose(const AdjList& graph) {
    AdjList transpose_graph(graph.size());
    for (size_t u = 0; u < graph.size(); ++u) {
        for (size_t v : graph[u]) {
            transpose_graph[v].push_back(u);
        }
    }
    return transpose_graph;
}

std::list<std::list<size_t> > StronglyConnectedComponents(const AdjList& graph) {
    size_t n = graph.size();

    size_t look_next_origin_1_counter = 0;
    auto look_next_origin_1 = [&look_next_origin_1_counter]() {
        return look_next_origin_1_counter++;
    };
    int time_counter = 0;
    std::priority_queue<std::pair<int, size_t> > pq;// [finish time, node_idx]
    auto op_after_visit_1 = [&time_counter, &pq](size_t curr_node_idx, int) {
        pq.emplace(++time_counter, curr_node_idx);
    };
    DFS(graph, look_next_origin_1, [](size_t) { return 0; }, [](size_t, int) {}, op_after_visit_1);

    AdjList transpose_graph = Transpose(graph);

    auto look_next_origin_2 = [n, &pq]() {
        if (pq.empty()) { return n; }
        size_t v = pq.top().second;
        pq.pop();
        return v;
    };
    std::list<std::list<size_t> > scc;
    auto op_before_component_2 = [&scc](size_t) { scc.emplace_back(); return 0; };
    auto op_start_visit_2 = [&scc](size_t node, int) { scc.back().push_back(node); };
    DFS(transpose_graph, look_next_origin_2, op_before_component_2, op_start_visit_2, [](size_t, int) {});

    return scc;
}

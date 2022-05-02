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

std::vector<std::vector<size_t> > StronglyConnectedComponents(const AdjList& graph) {
    size_t n = graph.size();

    // topological sort
    size_t look_next_origin_1_counter = 0;
    auto look_next_origin_1 = [&look_next_origin_1_counter]() {
        return look_next_origin_1_counter++;
    };
    std::vector<size_t> topo_sort;
    topo_sort.reserve(n + 1);
    topo_sort.push_back(n);// for the purpose of stopping DFS
    auto op_after_visit_1 = [&topo_sort](size_t curr_node_idx, int) {
        topo_sort.push_back(curr_node_idx);
    };
    DFS(graph, look_next_origin_1, [](size_t) { return 0; }, [](size_t, int) {}, op_after_visit_1);

    AdjList transpose_graph = Transpose(graph);

    // find strongly connected components
    auto look_next_origin_2 = [&topo_sort]() {
        size_t v = topo_sort.back();
        topo_sort.pop_back();
        return v;
    };
    std::vector<std::vector<size_t> > scc;
    auto op_before_component_2 = [&scc](size_t) { scc.emplace_back(); return 0; };
    auto op_start_visit_2 = [&scc](size_t node, int) { scc.back().push_back(node); };
    DFS(transpose_graph, look_next_origin_2, op_before_component_2, op_start_visit_2, [](size_t, int) {});

    return scc;
}

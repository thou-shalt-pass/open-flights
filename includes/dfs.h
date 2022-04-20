#ifndef _DFS_H
#define _DFS_H

#include <functional>

#include "type.h"

/**
 * @brief abstract DFS operation
 * 
 * @param graph adjacency list
 * @param look_next_origin function object that 
 * return the next node in the origin considering sequence; 
 * return a number greater than or equal to the graph size to stop DFS 
 * @param op_before_component function object that 
 * op_before_component(origin_idx) is called before the start of component traversal; 
 * return component_handle that will be passed into op_after_pop
 * @param op_start_visit function object that 
 * op_start_visit(curr_node_idx, component_handle) is called after the node is poped from the stack
 * @param op_after_visit function object that 
 * op_after_visit(curr_node_idx, component_handle) is called after the node is finished from visiting
 */
template <typename LookNextOrigin, typename OpBeforeComponent, typename OpBeforeVisit, typename OpAfterVisit>
void DFS(const AdjList& graph, LookNextOrigin look_next_origin, 
        OpBeforeComponent op_before_component, OpBeforeVisit op_start_visit, OpAfterVisit op_after_visit) {
    size_t n = graph.size(), origin;
    std::vector<bool> visited(graph.size(), false);
    std::function<void(size_t, int)> dfs_visit;
    dfs_visit = [&](size_t u, int component_handle) {
        op_start_visit(u, component_handle);
        for (size_t v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dfs_visit(v, component_handle);
            }
        }
        op_after_visit(u, component_handle);
    };
    while ((origin = look_next_origin()) < n) {
        if (visited[origin]) { continue; }
        visited[origin] = true;
        int component_handle = op_before_component(origin);
        dfs_visit(origin, component_handle);
    }
}

#endif
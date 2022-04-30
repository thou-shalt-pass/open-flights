#include <cassert>
#include <fstream>
#include <iostream>
#include <tuple>

#include "all_pairs_shortest_paths.h"
#include "data.h"
#include "dfs.h"

void RunDFS(const Data& data, const std::string& origin_code, std::ostream& os) {
    size_t n = data.GetAdjList().size(), v;

    try {
        v = data.GetIdx(origin_code);
    } catch (const std::out_of_range& e) {
        os << "Invalid IATA code\n";
        return;
    }

    size_t i = 0;
    auto look_next_origin = [n, &i, v]() {
        if (i == n) {
            return n;
        }
        ++i;
        return (v + i - 1) % n;
    };

    auto op_before_component = [&os, &data](size_t origin_idx) {
        os << "New Component where the origin is " << data.GetNode(origin_idx).iata_code << '\n';
        return origin_idx;
    };

    auto op_start_visit = [&os, &data](size_t curr_node_idx, size_t component_handle) {
        const Node& node = data.GetNode(curr_node_idx);
        os << "Start visiting " << node.iata_code << " (" << node.city << ")" << '\n';
    };

    auto op_after_visit = [&os, &data](size_t curr_node_idx, size_t component_handle) {
        const Node& node = data.GetNode(curr_node_idx);
        os << "Finish visiting " << node.iata_code << " (" << node.city << ")" << '\n';
    };

    DFS(data.GetAdjList(), look_next_origin, op_before_component, op_start_visit, op_after_visit);
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
        output_unzip_cmd("tar -xf result.tar.gz");

    system(output_unzip_cmd.c_str());
    std::string line;

    std::ifstream airport_ori_ifs(input_filename_airport), airline_ori_ifs(input_filename_airline);
    Data data_ori(airport_ori_ifs, airline_ori_ifs);
    airport_ori_ifs.close();
    airline_ori_ifs.close();

    std::ifstream airport_scc_ifs(output_filename_airport_largest_scc), airline_scc_ifs(output_filename_airline_largest_scc);
    Data data_scc(airport_scc_ifs, airline_scc_ifs);
    airport_scc_ifs.close();
    airline_scc_ifs.close();

    size_t n_ori = data_ori.GetAdjList().size(), n_scc = data_scc.GetAdjList().size();

    std::vector<size_t> node_to_scc(n_ori, std::numeric_limits<size_t>::max());// maps node to scc
    std::ifstream scc_is(output_filename_scc);
    size_t scc_counter = 0;
    while (std::getline(scc_is, line)) {
        std::vector<std::string> spl = Split(line, ',');
        for (const std::string& s : spl) {
            node_to_scc[std::stoul(s)] = scc_counter;
        }
        ++scc_counter;
    }

    // node idx in the order of importance
    std::vector<size_t> importance_order(n_scc);
    // node importnace where idx of the array is idx of the node (tuple: [order, it, lu, gaussian])
    std::vector<std::tuple<size_t, double, double, double> > importance(n_scc);
    std::ifstream importance_it_ifs(output_filename_importance_it), 
        importance_lu_ifs(output_filename_importance_lu), 
        importance_gaussian_ifs(output_filename_importance_gaussian);
    for (size_t i = 0; i < n_scc; ++i) {
        // iteration
        std::getline(importance_it_ifs, line, ',');
        double importance_it = std::stod(line);
        std::getline(importance_it_ifs, line, '\n');
        size_t idx = std::stoul(line);
        // lu
        std::getline(importance_lu_ifs, line, ',');
        double importance_lu = std::stod(line);
        std::getline(importance_lu_ifs, line, '\n');
        // gaussian
        std::getline(importance_gaussian_ifs, line, ',');
        double importance_gaussian = std::stod(line);
        std::getline(importance_gaussian_ifs, line, '\n');
        // store
        importance_order[i] = idx;
        importance[idx] = std::make_tuple(i, importance_it, importance_lu, importance_gaussian);
    }
    importance_it_ifs.close();
    importance_lu_ifs.close();
    importance_gaussian_ifs.close();

    Matrix<unsigned> apsp_distance(n_ori, std::vector<unsigned>(n_ori));
    Matrix<size_t> apsp_next(n_ori, std::vector<size_t>(n_ori));
    std::ifstream apsp_distance_ifs(output_filename_apsp_distance), apsp_next_ifs(output_filename_apsp_next);
    for (size_t i = 0; i < n_ori; ++i) {
        for (size_t j = 0; j < n_ori - 1; ++j) {
            std::getline(apsp_distance_ifs, line, ',');
            apsp_distance[i][j] = std::stoul(line);
            std::getline(apsp_next_ifs, line, ',');
            apsp_next[i][j] = std::stoul(line);
        }
        std::getline(apsp_distance_ifs, line, '\n');
        apsp_distance[i][n_ori - 1] = std::stoul(line);
        std::getline(apsp_next_ifs, line, '\n');
        apsp_next[i][n_ori - 1] = std::stoul(line);
    }
    apsp_distance_ifs.close();
    apsp_next_ifs.close();

    std::cout << "Initialization finished\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) { break; }
        std::vector<std::string> spl = Split(line, ' ');
        if (spl.size() == 0) {
            continue;
        }
        if (spl[0] == "exit" || spl[0] == "q") {
            std::cout << "Bye\n";
            break;
        }
        if (spl[0] == "dfs") {
            if (spl.size() != 2) {
                std::cout << "Usage: dfs origin-code\n";
                continue;
            }
            RunDFS(data_ori, spl[1], std::cout);
        } else if (spl[0] == "scc") {
            // find the scc idx of the airport
            if (spl.size() != 2) {
                std::cout << "Usage: scc code\n";
                continue;
            }
            size_t v;
            try {
                v = data_ori.GetIdx(spl[1]);
            } catch (const std::out_of_range& e) {
                std::cout << "Invalid IATA code\n";
                continue;
            }
            std::cout << "The airport is in the strongly connected component " << node_to_scc[v] << '\n';
        } else if (spl[0] == "sp") {
            // find the shortest path
            if (spl.size() != 3) {
                std::cout << "Usage: sp src-code dst-code\n";
                continue;
            }
            size_t src, dst;
            try {
                src = data_ori.GetIdx(spl[1]);
            } catch (const std::out_of_range& e) {
                std::cout << "Invalid IATA code for source airport\n";
                continue;
            }
            try {
                dst = data_ori.GetIdx(spl[2]);
            } catch (const std::out_of_range& e) {
                std::cout << "Invalid IATA code for destination airport\n";
                continue;
            }
            if (apsp_distance[src][dst] >= kNoAirline) {
                std::cout << spl[1] << " and " << spl[2] << " are not connected\n";
                continue;
            }
            std::cout << "Distance of the shortest path: " << apsp_distance[src][dst] << '\n';
            std::vector<size_t> path = PathReconstruction(apsp_next, src, dst);
            for (size_t i = 0; i < path.size() - 1; ++i) {
                std::cout << data_ori.GetNode(path[i]).iata_code << " -> ";
            }
            std::cout << data_ori.GetNode(path[path.size() - 1]).iata_code << '\n';
        } else if (spl[0] == "top") {
            if (spl.size() != 2) {
                std::cout << "Usage: top limit\n";
                continue;
            }
            size_t limit = std::stoul(spl[1]);
            if (limit > n_scc) {
                std::cout << "There are only " << n_scc << " airports in the largest strongly connected component\n";
                continue;
            }
            printf("%-5s | %-7s | %-7s | %-7s | %-5s | %-18s | %-20s\n", 
                "Order", "Iter", "LU", "Gaus", "Code", "City", "Airport Name");
            for (size_t i = 0; i < limit; ++i) {
                size_t v = importance_order[i];
                double importance_it = std::get<1>(importance[v]), 
                    importance_lu = std::get<2>(importance[v]), 
                    importance_gaussian = std::get<3>(importance[v]);
                const Node& node = data_scc.GetNode(v);
                printf("%5lu | %.5f | %.5f | %.5f | %-5s | %-18s | %-20s\n", 
                    (size_t)i + 1, importance_it, importance_lu, importance_gaussian, 
                    node.iata_code.c_str(), node.city.c_str(), node.airport_name.c_str());
            }
        } else if (spl[0] == "rank") {
            if (spl.size() != 2) {
                std::cout << "Usage: rank code\n";
                continue;
            }
            size_t v;
            try {
                v = data_scc.GetIdx(spl[1]);
            } catch (const std::out_of_range& e) {
                std::cout << "Invalid IATA code or the airport is not in the largest connected component\n";
                continue;
            }
            size_t rank = std::get<0>(importance[v]);
            double importance_it = std::get<1>(importance[v]), 
                importance_lu = std::get<2>(importance[v]), 
                importance_gaussian = std::get<3>(importance[v]);
            const Node& node = data_scc.GetNode(v);
            printf("%-5s | %-7s | %-7s | %-7s | %-5s | %-18s | %-20s\n", 
                "Order", "Iter", "LU", "Gaus", "Code", "City", "Airport Name");
            printf("%5lu | %.5f | %.5f | %.5f | %-5s | %-18s | %-20s\n", 
                rank, importance_it, importance_lu, importance_gaussian, 
                node.iata_code.c_str(), node.city.c_str(), node.airport_name.c_str());
        } else {
            std::cout << "Usage: \n- dfs origin-code\n- scc code\n- sp src-code dst-code\n- top limit\n- rank code\n";
        }
    }

    return 0;
}

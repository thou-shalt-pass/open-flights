#include <cassert>
#include <fstream>
#include <iostream>
#include <tuple>

#include "all_pairs_shortest_paths.h"
#include "data.h"
#include "dfs.h"

Data ReadData(const std::string& airport_filename, const std::string& airline_filename) {
    std::ifstream airport_ifs(airport_filename), airline_ifs(airline_filename);
    Data data(airport_ifs, airline_ifs);
    airport_ifs.close();
    airline_ifs.close();
    return data;
}

std::vector<size_t> ReadSCCResult(const Data& data, const std::string& scc_result_filename) {
    size_t n = data.GetAdjList().size();
    std::ifstream ifs(scc_result_filename);
    std::vector<size_t> node_to_scc(n, std::numeric_limits<size_t>::max());// maps node to scc
    size_t scc_counter = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        std::vector<std::string> spl = Split(line, ',');
        for (const std::string& s : spl) {
            node_to_scc[std::stoul(s)] = scc_counter;
        }
        ++scc_counter;
    }
    ifs.close();
    return node_to_scc;
}

ImportanceIntegrationResult ReadImportanceResult(const Data& data, const std::string& it_result_filename, 
        const std::string& lu_result_filename, const std::string& gaussian_result_filename) {
    size_t n = data.GetAdjList().size();
    ImportanceIntegrationResult result(n);
    std::ifstream importance_it_ifs(it_result_filename), 
        importance_lu_ifs(lu_result_filename), 
        importance_gaussian_ifs(gaussian_result_filename);
    std::string line;
    for (size_t i = 0; i < n; ++i) {
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
        result.Set(i, idx, importance_it, importance_lu, importance_gaussian);
    }
    importance_it_ifs.close();
    importance_lu_ifs.close();
    importance_gaussian_ifs.close();
    return result;
}

APSPResult ReadAPSPResult(size_t n, const std::string& distance_result_filename, 
        const std::string& next_result_filename) {
    APSPResult result(n);
    std::ifstream apsp_distance_ifs(distance_result_filename), apsp_next_ifs(next_result_filename);
    std::string line;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n - 1; ++j) {
            std::getline(apsp_distance_ifs, line, ',');
            result.distance[i][j] = std::stoul(line);
            std::getline(apsp_next_ifs, line, ',');
            result.next[i][j] = std::stoul(line);
        }
        std::getline(apsp_distance_ifs, line, '\n');
        result.distance[i][n - 1] = std::stoul(line);
        std::getline(apsp_next_ifs, line, '\n');
        result.next[i][n - 1] = std::stoul(line);
    }
    apsp_distance_ifs.close();
    apsp_next_ifs.close();
    return result;
}

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

    auto op_start_visit = [&os, &data](size_t curr_node_idx, size_t) {
        const Node& node = data.GetNode(curr_node_idx);
        os << "Start visiting " << node.iata_code << " (" << node.city << ")" << '\n';
    };

    auto op_after_visit = [&os, &data](size_t curr_node_idx, size_t) {
        const Node& node = data.GetNode(curr_node_idx);
        os << "Finish visiting " << node.iata_code << " (" << node.city << ")" << '\n';
    };

    DFS(data.GetAdjList(), look_next_origin, op_before_component, op_start_visit, op_after_visit);
}

void InterpretFindSCCIdx(const Data& data, const std::vector<size_t>& node_to_scc, 
        const std::string& code, std::ostream& os) {
    size_t v;
    try {
        v = data.GetIdx(code);
    } catch (const std::out_of_range& e) {
        os << "Invalid IATA code\n";
        return;
    }
    os << "The airport is in the strongly connected component " << node_to_scc[v] << '\n';
}

void InterpretFindShortestPath(const Data& data, const APSPResult& apsp_result, 
        const std::string& src_code, const std::string& dst_code, std::ostream& os) {
    size_t src, dst;
    try {
        src = data.GetIdx(src_code);
    } catch (const std::out_of_range& e) {
        os << "Invalid IATA code for source airport\n";
        return;
    }
    try {
        dst = data.GetIdx(dst_code);
    } catch (const std::out_of_range& e) {
        os << "Invalid IATA code for destination airport\n";
        return;
    }
    if (apsp_result.distance[src][dst] >= kNoAirline) {
        os << src_code << " and " << dst_code << " are not connected\n";
        return;
    }
    os << "Distance of the shortest path: " << apsp_result.distance[src][dst] << '\n';
    std::vector<size_t> path = PathReconstruction(apsp_result.next, src, dst);
    for (size_t i = 0; i < path.size() - 1; ++i) {
        os << data.GetNode(path[i]).iata_code << " -> ";
    }
    os << data.GetNode(path[path.size() - 1]).iata_code << '\n';
}

void InterpretFindTopImportance(const Data& data_largest_scc, 
        const ImportanceIntegrationResult& importance_largest_scc, size_t limit, std::ostream& os) {
    if (limit == 0 || limit > data_largest_scc.GetAdjList().size()) {
        os << "limit should with in the range [1, " << data_largest_scc.GetAdjList().size() << "]\n";
        return;
    }
    os << "Order | Iter    | LU       | Gaussian | Code  | City               | Airport Name\n";
    char buf[512];
    for (size_t i = 0; i < limit; ++i) {
        size_t v = importance_largest_scc.order_to_idx[i];
        const Node& node = data_largest_scc.GetNode(v);
        snprintf(buf, sizeof(buf), "%5lu | %.5f | %.5f | %.5f | %-5s | %-18s | %-20s\n", 
            i + 1, importance_largest_scc.idx_to_imp_it[v], 
            importance_largest_scc.idx_to_imp_lu[v], importance_largest_scc.idx_to_imp_gaussian[v], 
            node.iata_code.c_str(), node.city.c_str(), node.airport_name.c_str());
        os << buf;
    }
}

void InterpretAirportImportance(const Data& data_largest_scc, 
        const ImportanceIntegrationResult& importance_largest_scc, const std::string& code, std::ostream& os) {
    size_t v;
    try {
        v = data_largest_scc.GetIdx(code);
    } catch (const std::out_of_range& e) {
        std::cout << "Invalid IATA code or the airport is not in the largest connected component\n";
        return;
    }
    const Node& node = data_largest_scc.GetNode(v);
    os << "Order | Iter    | LU       | Gaussian | Code  | City               | Airport Name\n";
    char buf[512];
    snprintf(buf, sizeof(buf), "%5lu | %.5f | %.5f | %.5f | %-5s | %-18s | %-20s\n", 
        importance_largest_scc.idx_to_order[v], importance_largest_scc.idx_to_imp_it[v], 
        importance_largest_scc.idx_to_imp_lu[v], importance_largest_scc.idx_to_imp_gaussian[v], 
        node.iata_code.c_str(), node.city.c_str(), node.airport_name.c_str());
    os << buf;
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

    // unzip result
    system(output_unzip_cmd.c_str());

    // read data and result; init data structures
    Data data_ori = ReadData(input_filename_airport, input_filename_airline);
    std::vector<size_t> node_to_scc = ReadSCCResult(data_ori, output_filename_scc);// maps node to scc
    Data data_largest_scc = ReadData(output_filename_airport_largest_scc, output_filename_airline_largest_scc);
    ImportanceIntegrationResult importance_largest_scc = ReadImportanceResult(data_largest_scc, output_filename_importance_it, output_filename_importance_lu, output_filename_importance_gaussian);
    APSPResult apsp_result = ReadAPSPResult(data_ori.GetAdjList().size(), output_filename_apsp_distance, output_filename_apsp_next);

    std::cout << "Initialization finished\n";

    // interact with users
    while (true) {
        std::cout << "> ";
        std::string line;
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
            InterpretFindSCCIdx(data_ori, node_to_scc, spl[1], std::cout);
        } else if (spl[0] == "sp") {
            // find the shortest path
            if (spl.size() != 3) {
                std::cout << "Usage: sp src-code dst-code\n";
                continue;
            }
            InterpretFindShortestPath(data_ori, apsp_result, spl[1], spl[2], std::cout);
        } else if (spl[0] == "top") {
            // find top importance airports
            if (spl.size() != 2) {
                std::cout << "Usage: top limit\n";
                continue;
            }
            try {
                InterpretFindTopImportance(data_largest_scc, importance_largest_scc, std::stoul(spl[1]), std::cout);
            } catch (const std::invalid_argument& e) {
                std::cout << "limit should be an integer\n";
                continue;
            }
        } else if (spl[0] == "rank") {
            // find airport's importance
            if (spl.size() != 2) {
                std::cout << "Usage: rank code\n";
                continue;
            }
            InterpretAirportImportance(data_largest_scc, importance_largest_scc, spl[1], std::cout);
        } else {
            std::cout << "Usage: \n- dfs origin-code\n- scc code\n- sp src-code dst-code\n- top limit\n- rank code\n";
        }
    }

    return 0;
}

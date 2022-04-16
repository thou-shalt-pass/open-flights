#include <fstream>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>

#include <unordered_set>

#include "data.h"

Data::Data(const std::string& airport_filename, 
    const std::string& airline_filename) {
    ReadAirport(airport_filename);
    ReadAirline(airline_filename);
}

void Data::ReadAirport(const std::string& airport_filename) {
    std::ifstream ifs { airport_filename };
    if (!ifs.is_open()) { throw std::runtime_error("invalid file path."); }

    // read each line
    std::string line;
    while (std::getline(ifs, line)) {
        std::vector<std::string> info;
        info.reserve(5);
        bool quotation = false;
        std::string str;

        for (size_t a = 0; a < line.size(); a++) {
            char curr = line[a];
            // outside of a quote
            if (!quotation) {
                // start a quote
                if (curr == '"') {
                    quotation = true;
                    str.push_back('"');
                } else if (curr == ',' || a == line.size() - 1) {
                    info.push_back(str);
                    str = "";
                } else {
                    str.push_back(curr);
                }
            }
            // within a quote
            else {
                // end a quote
                if (curr == '"') { 
                    quotation = false;
                    str.push_back('"');
                } else {
                    str.push_back(curr);
                }
            }
        }
    
        idx_to_node_.emplace_back(std::forward<std::string>(info[0]), 
            std::forward<std::string>(info[1]), 
            std::forward<std::string>(info[2]), 
            std::stod(info[3]), std::stod(info[4]));
        code_to_idx_.emplace(idx_to_node_.back().iata_code, 
            idx_to_node_.size() - 1);
    }
}

void Data::ReadAirline(const std::string& airline_filename) {
    size_t airport_size = idx_to_node_.size();
    adj_list_.resize(airport_size);
    adj_matrix_.resize(airport_size, std::vector<Edge>(airport_size, kNoAirline));

    std::ifstream ifs { airline_filename };
    if (!ifs.is_open()) { throw std::runtime_error("invalid file path."); }
    // read each line
    std::string line;
    while (std::getline(ifs, line)) {
        std::string src_code(line.begin(), line.begin() + 3), 
            dst_code(line.begin() + 4, line.begin() + 7);
        size_t src_idx = code_to_idx_.at(src_code);
        size_t dst_idx = code_to_idx_.at(dst_code);
        adj_list_[src_idx].push_back(dst_idx);
        adj_matrix_[src_idx][dst_idx].distance = 10;// TODO: calc dist
    }
}

const AdjList& Data::GetAdjList() const { return adj_list_; }

const AdjMatrix& Data::GetAdjMatrix() const { return adj_matrix_; }

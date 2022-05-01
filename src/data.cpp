#include <cmath>
#include <istream>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "data.h"

std::vector<std::string> Split(const std::string& line, char delimiter) {
    std::vector<std::string> info;
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
            } else if (curr == delimiter) {
                info.push_back(str);
                str = "";
            } else if (a == line.size() - 1) {
                str.push_back(curr);
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
    return info;
}

Data::Data(std::istream& airport_is, std::istream& airline_is) {
    ReadAirport(airport_is);
    ReadAirline(airline_is);
}

void Data::ReadAirport(std::istream& airport_is) {
    std::string line;
    while (std::getline(airport_is, line)) {
        std::vector<std::string> info = Split(line, ',');
        idx_to_node_.emplace_back(std::move(info[0]), 
            std::move(info[1]), 
            std::move(info[2]), 
            std::stod(info[3]), std::stod(info[4]));
        code_to_idx_.emplace(idx_to_node_.back().iata_code, 
            idx_to_node_.size() - 1);
    }
}

// convert degrees to radian
long double Data::ToRadiant(const long double degree) {
    long double ratio = (M_PI) / 180;
    return (ratio * degree);
}

constexpr int kEarthRadius = 6371;

// Haversine formula to calculate distance between 2 points on a sphere given longtitudes and latitudes
unsigned Data::Distance(long double lat1, long double long1, long double lat2, long double long2) {
    lat1 = ToRadiant(lat1);
    lat2 = ToRadiant(lat2);
    long1 = ToRadiant(long1);
    long2 = ToRadiant(long2);
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
    long double result = pow(sin(dlat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong/2), 2);
    result = 2 * asin(sqrt(result)) * kEarthRadius;
    return static_cast<unsigned>(result);
}
 
void Data::ReadAirline(std::istream& airline_is) {
    size_t airport_size = idx_to_node_.size();
    std::vector<std::unordered_set<size_t> > adj_list_set(airport_size);
    adj_list_.reserve(airport_size);
    adj_matrix_.resize(airport_size, std::vector<Edge>(airport_size, kNoAirline));

    std::string line;
    while (std::getline(airline_is, line)) {
        std::string src_code(line.begin(), line.begin() + 3), 
            dst_code(line.begin() + 4, line.begin() + 7);
        if (code_to_idx_.count(src_code) == 0 || code_to_idx_.count(dst_code) == 0) {
            // ignore edges that contain nodes which are not exist
            continue;
        }
        size_t src_idx = code_to_idx_.at(src_code);
        size_t dst_idx = code_to_idx_.at(dst_code);
        adj_list_set[src_idx].insert(dst_idx);
        adj_matrix_[src_idx][dst_idx].distance = Distance(idx_to_node_[src_idx].latitude, 
            idx_to_node_[src_idx].longitude, idx_to_node_[dst_idx].latitude, 
            idx_to_node_[dst_idx].longitude);
    }

    for (size_t i = 0; i < airport_size; ++i) {
        adj_list_.emplace_back(adj_list_set[i].begin(), adj_list_set[i].end());
    }
}

const AdjList& Data::GetAdjList() const { return adj_list_; }

const AdjMatrix& Data::GetAdjMatrix() const { return adj_matrix_; }

const Node& Data::GetNode(size_t idx) const { return idx_to_node_[idx]; }

size_t Data::GetIdx(const std::string& code) const { return code_to_idx_.at(code); }

Data::Data(const Data& data_ori, const std::vector<size_t>& allowed_idx) {
    size_t n_ori = data_ori.GetAdjList().size(), n_curr = allowed_idx.size();
    // allowed_idx maps current idx to original idx
    // ori_idx_to_curr_idx maps original idx to current idx
    std::vector<size_t> ori_idx_to_curr_idx(n_ori, std::numeric_limits<size_t>::max());

    // construct idx_to_node_ and code_to_idx_
    idx_to_node_.reserve(n_curr);
    for (size_t i = 0; i < n_curr; ++i) {
        ori_idx_to_curr_idx[allowed_idx[i]] = i;
        const Node& node = data_ori.idx_to_node_[allowed_idx[i]];
        idx_to_node_.push_back(node);
        code_to_idx_[node.iata_code] = i;
    }

    // construct adj_list_ and adj_matrix_
    adj_list_.resize(n_curr);
    adj_matrix_.resize(n_curr, std::vector<Edge>(n_curr, kNoAirline));
    for (size_t curr_idx = 0; curr_idx < n_curr; ++curr_idx) {
        size_t ori_idx = allowed_idx[curr_idx];
        for (size_t ori_neighbor_idx : data_ori.adj_list_[ori_idx]) {
            if (ori_idx_to_curr_idx[ori_neighbor_idx] != std::numeric_limits<size_t>::max()) {
                size_t curr_neighbor_idx = ori_idx_to_curr_idx[ori_neighbor_idx];
                adj_list_[curr_idx].push_back(curr_neighbor_idx);
                adj_matrix_[curr_idx][curr_neighbor_idx] = data_ori.adj_matrix_[ori_idx][ori_neighbor_idx];
            }
        }
    }
}

Data ReadData(const std::string& airport_filename, const std::string& airline_filename) {
    std::ifstream airport_ifs(airport_filename), airline_ifs(airline_filename);
    Data data(airport_ifs, airline_ifs);
    airport_ifs.close();
    airline_ifs.close();
    return data;
}

void FilterAirports(std::ostream& os, std::istream& is, 
        const std::unordered_set<std::string>& allowed_codes) {
    std::string line;
    while (std::getline(is, line)) {
        std::vector<std::string> info = Split(line, ',');
        if (allowed_codes.count(info[2]) > 0) {
            os << line << "\n";
        }
    }
}

void FilterAirlines(std::ostream& os, std::istream& is,
         const std::unordered_set<std::string>& allowed_codes) {
    std::string line;
    while (std::getline(is, line)) {
        if (allowed_codes.count(line.substr(0, 3)) > 0 && allowed_codes.count(line.substr(4, 3)) > 0) {
            os << line << "\n";
        }
    }
}

void FilterAirports(const std::string& out_filename, const std::string& in_filename, 
		const std::unordered_set<std::string>& allowed_codes) {
    std::ifstream ifs(in_filename);
    std::ofstream ofs(out_filename);

    FilterAirports(ofs, ifs, allowed_codes);

    ifs.close();
    ofs.close();
}

void FilterAirlines(const std::string& out_filename, const std::string& in_filename, 
		const std::unordered_set<std::string>& allowed_codes) {
    std::ifstream ifs(in_filename);
    std::ofstream ofs(out_filename);

    FilterAirlines(ofs, ifs, allowed_codes);

    ifs.close();
    ofs.close();
}

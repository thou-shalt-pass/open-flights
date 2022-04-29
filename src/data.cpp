#include <cmath>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "data.h"

std::vector<std::string> SplitAirportDataLine(const std::string& line) {
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
    return info;
}

Data::Data(std::istream& airport_is, std::istream& airline_is) {
    ReadAirport(airport_is);
    ReadAirline(airline_is);
}

void Data::ReadAirport(std::istream& airport_is) {
    std::string line;
    while (std::getline(airport_is, line)) {
        std::vector<std::string> info = SplitAirportDataLine(line);
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

// Haversine formula to calculate distance between 2 points on a sphere given longtitudes and latitudes
unsigned Data::Distance(long double lat1, long double long1, long double lat2, long double long2) {
    lat1 = ToRadiant(lat1);
    lat2 = ToRadiant(lat2);
    long1 = ToRadiant(long1);
    long2 = ToRadiant(long2);
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
    long double result = pow(sin(dlat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong/2), 2);
    result = 2 * asin(sqrt(result));

    // earth radius = 6371 km
    result *= 6371;
    return unsigned (result);

}
 
void Data::ReadAirline(std::istream& airline_is) {
    size_t airport_size = idx_to_node_.size();
    adj_list_set_.resize(airport_size);
    adj_list_.reserve(airport_size);
    adj_matrix_.resize(airport_size, std::vector<Edge>(airport_size, kNoAirline));

    std::string line;
    while (std::getline(airline_is, line)) {
        std::string src_code(line.begin(), line.begin() + 3), 
            dst_code(line.begin() + 4, line.begin() + 7);
        size_t src_idx = code_to_idx_.at(src_code);
        size_t dst_idx = code_to_idx_.at(dst_code);
        adj_list_set_[src_idx].insert(dst_idx);
        adj_matrix_[src_idx][dst_idx].distance = Distance(idx_to_node_[src_idx].latitude, 
            idx_to_node_[src_idx].longitude, idx_to_node_[dst_idx].latitude, 
            idx_to_node_[dst_idx].longitude);
    }

    for (size_t i = 0; i < airport_size; ++i) {
        adj_list_.emplace_back(adj_list_set_[i].begin(), adj_list_set_[i].end());
    }
}

const AdjList& Data::GetAdjList() const { return adj_list_; }

const AdjMatrix& Data::GetAdjMatrix() const { return adj_matrix_; }

const Node& Data::GetNode(size_t idx) const { return idx_to_node_[idx]; }

void FilterAirports(std::ostream& os, std::istream& is, const std::unordered_set<std::string>& allowed_codes) {
    std::string line;
    while (std::getline(is, line)) {
        std::vector<std::string> info = SplitAirportDataLine(line);
        if (allowed_codes.count(info[2]) > 0) {
            os << line << "\n";
        }
    }
}

void FilterAirlines(std::ostream& os, std::istream& is, const std::unordered_set<std::string>& allowed_codes) {
    std::string line;
    while (std::getline(is, line)) {
        if (allowed_codes.count(line.substr(0, 3)) > 0 && allowed_codes.count(line.substr(4, 3)) > 0) {
            os << line << "\n";
        }
    }
}

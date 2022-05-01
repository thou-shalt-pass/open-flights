#ifndef _DATA_H
#define _DATA_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "type.h"

class Data {
public:
	/**
	 * @brief store a simple directed graph
	 * 
	 * @param airport_is 
	 * @param airline_is 
	 */
	Data(std::istream& airport_is, std::istream& airline_is);
	/**
	 * @brief Filter data
	 * 
	 * @param data_ori original data object
	 * @param allowed_idx all idx in this vector must be valid (in the range; no repeat elements)
	 */
	Data(const Data& data_ori, const std::vector<size_t>& allowed_idx);
	const AdjList& GetAdjList() const;
	const AdjMatrix& GetAdjMatrix() const;
	long double ToRadiant(const long double degree);
	unsigned Distance(long double lat1, long double long1, long double lat2, long double long2);
	const Node& GetNode(size_t idx) const;
	size_t GetIdx(const std::string& code) const;
private:
	void ReadAirport(std::istream& airport_is);
	void ReadAirline(std::istream& airline_is);

	std::vector<Node> idx_to_node_;// map index to node
	std::unordered_map<std::string, size_t> code_to_idx_;// map code to idx
	AdjList adj_list_;
	AdjMatrix adj_matrix_;
};

Data ReadData(const std::string& airport_filename, const std::string& airline_filename);

std::vector<std::string> Split(const std::string& line, char delimiter);

void FilterAirports(std::ostream& os, std::istream& is, 
		const std::unordered_set<std::string>& allowed_codes);
void FilterAirlines(std::ostream& os, std::istream& is, 
		const std::unordered_set<std::string>& allowed_codes);

void FilterAirports(const std::string& out_filename, const std::string& in_filename, 
		const std::unordered_set<std::string>& allowed_codes);
void FilterAirlines(const std::string& out_filename, const std::string& in_filename, 
		const std::unordered_set<std::string>& allowed_codes);


#endif
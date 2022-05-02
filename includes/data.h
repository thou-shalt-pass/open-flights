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
	 * @param airport_is airport dataset istream
	 * @param airline_is airline dataset istream
	 */
	Data(std::istream& airport_is, std::istream& airline_is);

	/**
	 * @brief Filter data
	 * 
	 * @param data_ori original data object
	 * @param allowed_idx all idx in this vector must be valid (in the range; no repeat elements)
	 */
	Data(const Data& data_ori, const std::vector<size_t>& allowed_idx);

	/**
	 * @brief get the adjacency list represents the simple directed grpah
	 * 
	 * @return const AdjList& 
	 */
	const AdjList& GetAdjList() const;

	/**
	 * @brief get the adjacency matrix represents the simple directed grpah
	 * 
	 * @return const AdjMatrix& 
	 */
	const AdjMatrix& GetAdjMatrix() const;

	/**
	 * @brief convert degree to radiant
	 * 
	 * @param degree 
	 * @return long double 
	 */
	long double ToRadiant(const long double degree);

	/**
	 * @brief get distance between two locations by using Haversine formula
	 * 
	 * @param lat1 latitude of location 1
	 * @param long1 longitude of location 1
	 * @param lat2 latitude of location 2
	 * @param long2 longitude of location 2
	 * @return unsigned 
	 */
	unsigned Distance(long double lat1, long double long1, long double lat2, long double long2);

	/**
	 * @brief get the Node object represents the graph
	 * 
	 * @param idx idx of the node in adj list and adj matrix
	 * @return const Node& 
	 */
	const Node& GetNode(size_t idx) const;

	/**
	 * @brief get idx of the node in adj list and adj matrix
	 * 
	 * @param code IATA code
	 * @return size_t 
	 */
	size_t GetIdx(const std::string& code) const;

private:
	/**
	 * @brief Helper of Data(std::istream& airport_is, std::istream& airline_is)
	 * 
	 * @param airport_is airport dataset istream
	 */
	void ReadAirport(std::istream& airport_is);

	/**
	 * @brief Helper of Data(std::istream& airport_is, std::istream& airline_is)
	 * 
	 * @param airline_is airport dataset istream
	 */
	void ReadAirline(std::istream& airline_is);

	std::vector<Node> idx_to_node_;// map index to node
	std::unordered_map<std::string, size_t> code_to_idx_;// map code to idx
	AdjList adj_list_;// adj list
	AdjMatrix adj_matrix_;// adj matrix
};

/**
 * @brief make Data object
 * 
 * @param airport_filename airport dataset filename
 * @param airline_filename airline dataset filename
 * @return Data 
 */
Data ReadData(const std::string& airport_filename, const std::string& airline_filename);

/**
 * @brief split utility function
 * 
 * @param line input str
 * @param delimiter delimiter
 * @return std::vector<std::string> 
 */
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
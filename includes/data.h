#ifndef _DATA_H
#define _DATA_H

#include <unordered_map>
#include <vector>
#include "type.h"

class Data {
public:
	Data(const std::string& airport_filename, const std::string& airline_filename);
	const AdjList& GetAdjList() const;
	const AdjMatrix& GetAdjMatrix() const;
	long double ToRadiant(const long double degree);
	unsigned Distance (long double lat1, long double long1, long double lat2, long double long2);
	
private:
	void ReadAirport(const std::string& airport_filename);
	void ReadAirline(const std::string& airline_filename);
	std::vector<Node> idx_to_node_;// map index to node
	std::unordered_map<std::string, size_t> code_to_idx_;// map code to idx
	AdjList adj_list_;
	AdjMatrix adj_matrix_;
};

#endif
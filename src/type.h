#ifndef _TYPE_H
#define _TYPE_H

#include <limits>
#include <list>
#include <string>
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T> >;

constexpr unsigned long long kNoAirline = std::numeric_limits<unsigned>::max();

struct Edge {
	unsigned distance;
};

struct Node{
	std::string city;
	std::string airport_name;
	std::string iata_code;
	double longitude;
	double latitude;
};

using AdjList = std::vector<std::list<size_t> >;
using AdjMatrix = Matrix<Edge>;

#endif
#ifndef _TYPE_H
#define _TYPE_H

#include <limits>
#include <list>
#include <string>
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T> >;

constexpr unsigned kNoAirline = (std::numeric_limits<unsigned>::max() >> 1) - 100000;

struct Edge {
	unsigned distance;

	Edge() {}
	Edge(unsigned distance) : distance(distance) {}
};

struct Node{
	std::string city;
	std::string airport_name;
	std::string iata_code;
	double longitude;
	double latitude;

	Node() {}
	Node(std::string&& city, std::string&& airport_name, std::string&& iata_code, 
		double longitude, double latitude) 
		: city(std::forward<std::string>(city)), 
		airport_name(std::forward<std::string>(airport_name)), 
		iata_code(std::forward<std::string>(iata_code)), 
		longitude(longitude), latitude(latitude) {}
};

using AdjList = std::vector<std::list<size_t> >;
using AdjMatrix = Matrix<Edge>;

#endif
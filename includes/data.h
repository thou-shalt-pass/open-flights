#ifndef _DATA_H
#define _DATA_H
#include <istream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

struct Edge{
    unsigned distance_;
};
struct Node{
    std::string city_;
	std::string airport_name_;
	std::string iata_code_;
	double longitude_;
	double latitude_;
};
class Data {
public:
	void read_airport();
	void read_airline();
	std::vector<Node> get_airports();
	void display(Node airprot);
	std::vector<Node> airports;
	std::vector<Edge> airlines;
};

#endif
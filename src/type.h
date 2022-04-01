#ifndef _TYPE_H
#define _TYPE_H

#include <limits>
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T> >;

constexpr unsigned long long kNoAirline = std::numeric_limits<unsigned long long>::max();

using AdjMatrix = Matrix<unsigned long long>;

struct Path {
	std::vector<size_t> airports;
	unsigned long long distance;
};

#endif
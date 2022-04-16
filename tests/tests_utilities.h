#ifndef _TESTS_UTILITIES_H
#define _TESTS_UTILITIES_H

#include "catch.hpp"

#include <cmath>
#include <unordered_set>
#include <vector>

void CheckDouble(double a, double b, double error);

void CheckVectorDouble(const std::vector<double>& a, const std::vector<double>& b, double error);

template <typename T>
void CheckVectorComb(const std::vector<T>& a, const std::vector<T>& b) {
    REQUIRE( a.size() == b.size() );
    std::unordered_set<T> table;
    for (const T& x : a) {
        REQUIRE( table.count(x) == 0 );
        table.insert(x);
    }
    for (const T& x : b) {
        REQUIRE( table.count(x) > 0 );
        table.erase(x);
    }
}

#endif
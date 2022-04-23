#ifndef _TESTS_UTILITIES_H
#define _TESTS_UTILITIES_H

#include "catch.hpp"

#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <vector>

void CheckDouble(double a, double b, double error);

void CheckVectorDouble(const std::vector<double>& a, const std::vector<double>& b, double error);

void CheckVectorDoubleWithScalarMultiple(const std::vector<double>& a, const std::vector<double>& b, double error);

template <typename InputIterator>
void CheckComb(InputIterator a_begin, InputIterator a_end, 
        InputIterator b_begin, InputIterator b_end) {
    std::unordered_set<typename std::iterator_traits<InputIterator>::value_type> set;

    while (a_begin != a_end) {
        REQUIRE( set.count(*a_begin) == 0 );
        set.insert(*a_begin);
        ++a_begin;
    }

    while (b_begin != b_end) {
        auto it = set.find(*b_begin);
        REQUIRE( it != set.end() );
        set.erase(*it);
        ++b_begin;
    }

    REQUIRE( set.size() == 0 );
}

template <typename InputIterator>
void CheckPartition(InputIterator a_begin, InputIterator a_end, 
        InputIterator b_begin, InputIterator b_end) {
    std::unordered_map<typename std::iterator_traits<InputIterator>::value_type::value_type, size_t> map;
    size_t counter = 0;

    while (a_begin != a_end) {
        REQUIRE( a_begin->cbegin() != a_begin->cend() );
        auto sub_it = a_begin->cbegin();

        while (sub_it != a_begin->cend()) {
            REQUIRE( map.count(*sub_it) == 0 );
            map[*sub_it] = counter;
            ++sub_it;
        }

        ++counter;
        ++a_begin;
    }

    std::vector<bool> visited(counter, false);

    while (b_begin != b_end) {
        REQUIRE( b_begin->cbegin() != b_end->cend() );
        auto sub_it = b_begin->cbegin();

        auto map_it = map.find(*sub_it);
        REQUIRE( map_it != map.end() );
        size_t curr_counter = map_it->second;
        REQUIRE( visited[curr_counter] == false );
        visited[curr_counter] = true;
        map.erase(map_it);
        ++sub_it;

        while (sub_it != b_begin->cend()) {
            map_it = map.find(*sub_it);
            REQUIRE( map_it != map.end() );
            REQUIRE( curr_counter == map_it->second );
            map.erase(map_it);
            ++sub_it;
        }

        ++b_begin;
    }
    
    REQUIRE( map.size() == 0 );
}

#endif
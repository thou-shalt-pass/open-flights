#include "catch.hpp"

#include <cmath>

#include "type.h"

#include "importance.h"

void CheckVectorDouble(const std::vector<double>& a, const std::vector<double>& b, double error) {
    REQUIRE( a.size() == b.size() );
    for (size_t i = 0; i < a.size(); ++i) {
        REQUIRE( std::abs(b[i] - a[i]) < error );
    }
}

TEST_CASE("Importance(const AdjList& graph)", "[importance_adj_list]") {
    AdjList graph {
        { 1, 2, 3 },
        { 2, 3 },
        { 0 },
        { 0, 2 }
    };
    std::vector<double> importance = Importance(graph);
    CheckVectorDouble(importance, { 0.38, 0.12, 0.29, 0.19 }, 0.01);
}

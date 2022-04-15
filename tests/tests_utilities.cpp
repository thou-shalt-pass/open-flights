#include "tests_utilities.h"

void CheckDouble(double a, double b, double error) {
    REQUIRE( std::abs(b - a) < error );
}

void CheckVectorDouble(const std::vector<double>& a, const std::vector<double>& b, double error) {
    REQUIRE( a.size() == b.size() );
    for (size_t i = 0; i < a.size(); ++i) {
        CheckDouble(a[i], b[i], error);
    }
}
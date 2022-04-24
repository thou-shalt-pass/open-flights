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

void CheckVectorSizet(const std::vector<size_t>& a, const std::vector<size_t>& b) {
    REQUIRE( a.size() == b.size() );
    for (size_t i = 0; i < a.size(); ++i) {
        REQUIRE(a[i] == b[i]);
    }
}

void CheckVectorDoubleWithScalarMultiple(const std::vector<double>& a, const std::vector<double>& b, double error) {
    double multiple = a[0] / b[0];
    std::vector<double> b_mult;
    b_mult.reserve(b.size());
    for (double x : b) {
        b_mult.push_back(x * multiple);
    }
    CheckVectorDouble(a, b_mult, error);
}

#include "tests_utilities.h"

double CheckDouble(double a, double b, double error) {
    double diff = std::abs(b - a);
    REQUIRE( diff < error );
    return diff;
}

double CheckVectorDouble(const std::vector<double>& a, const std::vector<double>& b, double error) {
    REQUIRE( a.size() == b.size() );
    double diff_peak = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        diff_peak = std::max(diff_peak, CheckDouble(a[i], b[i], error));
    }
    return diff_peak;
}

double CheckVectorDoubleWithScalarMultiple(const std::vector<double>& a, const std::vector<double>& b, double error) {
    double multiple = a[0] / b[0];
    std::vector<double> b_mult;
    b_mult.reserve(b.size());
    for (double x : b) {
        b_mult.push_back(x * multiple);
    }
    return CheckVectorDouble(a, b_mult, error);
}

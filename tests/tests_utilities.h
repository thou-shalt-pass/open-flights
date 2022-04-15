#ifndef _TESTS_UTILITIES_H
#define _TESTS_UTILITIES_H

#include "catch.hpp"

#include <cmath>
#include <vector>

void CheckDouble(double a, double b, double error);
void CheckVectorDouble(const std::vector<double>& a, const std::vector<double>& b, double error);

#endif
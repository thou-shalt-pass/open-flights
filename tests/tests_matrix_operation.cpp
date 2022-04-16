#include "tests_utilities.h"

#include "type.h"

#include "matrix_operation.h"

void PrintVector(const std::vector<double>& solution){
    for(size_t i = 0; i < solution.size(); i++){
        std::cout << solution[i] << " ";
    }
}

void HelpTestMatrixOperator(std::vector<double>& Solution, std::vector<double>& Expected){
    double scalar = Solution[0] / Expected[0];
    for(size_t i = 1; i < Expected.size(); i++){
        REQUIRE(Solution[i] / Expected[i] == scalar);
    }
}

TEST_CASE("FindOneDimNullSpace(const Matrix<double>& matrix)", "[find_1d_null_space]") {
    SECTION("2 * 2 Matrix 1"){
        Matrix<double> M { { -4, 3}, {4, -3}};
        std::vector<double> Solution = FindOneDimNullSpace(M);
        std::vector<double> Expected {3, 4};
        HelpTestMatrixOperator(Solution, Expected);
    }
}

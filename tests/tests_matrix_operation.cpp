#include "tests_utilities.h"

#include "type.h"

#include "matrix_operation.h"

// TEST_CASE("FindSquareMatrixOneDimNullSpace(const Matrix<double>& matrix)", "[find_1d_null_space]") {
//     SECTION("2 * 2 Matrix 1"){
//         Matrix<double> M { 
//             { -4, 3 }, 
//             { 4, -3 } 
//         };
//         std::vector<double> Solution = FindSquareMatrixOneDimNullSpace(M, 1e-15);
//         std::vector<double> Expected {3, 4};
//         CheckVectorDoubleWithScalarMultiple(Solution, Expected, 1e-15);
//     }
// }

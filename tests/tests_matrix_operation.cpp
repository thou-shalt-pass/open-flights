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

// TEST_CASE("One Dim Null Space 3 * 3"){
//     SECTION("1st Column Free"){
//         std::vector<std::vector<double> > matrix_double {{0, 6, 10},
//                                                         {0, 12, 13}};
//         std::vector< std::vector<Fraction> > coefficient = { {Fraction(-2), Fraction(1)} };
        
//         std::vector<std::vector<Fraction> > matrix; 
//         InitialMatrix(matrix_double, matrix);
//         std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
//         matrix.push_back(dependent_row[0]);
//         //Print2Dvector(matrix);

//         std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
//         std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
//         CheckMatrix(product, zeroVector(3));
//     }

//     SECTION("2nd Column Free"){
//         std::vector<std::vector<double> > matrix_double {{1, 0, 10},
//                                                         {0, 0, 27}};
//         std::vector< std::vector<Fraction> > coefficient = { {Fraction(4), Fraction(3)} };
        
//         std::vector<std::vector<Fraction> > matrix; 
//         InitialMatrix(matrix_double, matrix);
//         std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
//         matrix.push_back(dependent_row[0]);
//         //Print2Dvector(matrix);

//         std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
//         std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
//         CheckMatrix(product, zeroVector(3));
//     }

//     SECTION("3rd Column Free"){
//         std::vector<std::vector<double> > matrix_double {{2, 6, 10},
//                                                         {2, 9, 13}};
//         std::vector< std::vector<Fraction> > coefficient = { {Fraction(1), Fraction(2)} };
        
//         std::vector<std::vector<Fraction> > matrix; 
//         InitialMatrix(matrix_double, matrix);
//         std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
//         matrix.push_back(dependent_row[0]);
//         //Print2Dvector(matrix);

//         std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
//         std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
//         CheckMatrix(product, zeroVector(3));
//     }
// }

// TEST_CASE("One Dim Null Space 4 * 4"){
//     SECTION("1st Column Free"){
//         std::vector<std::vector<double> > matrix_double {{0, 0, 1, 5},
//                                                         {0, 4, 2, 3},
//                                                         {0, 3, 0, 2}};
//         std::vector< std::vector<Fraction> > coefficient = { {Fraction(3), Fraction(1), Fraction(5)} };
        
//         std::vector<std::vector<Fraction> > matrix; 
//         InitialMatrix(matrix_double, matrix);
//         std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
//         matrix.push_back(dependent_row[0]);
//         //Print2Dvector(matrix);

//         std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
//         std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
//         CheckMatrix(product, zeroVector(4));
//     }

//     SECTION("2nd Column Free"){
//         std::vector<std::vector<double> > matrix_double {{1, 4, 1, 5},
//                                                         {1, 4, 2, 3},
//                                                         {0, 0, 8, 2}};
//         std::vector< std::vector<Fraction> > coefficient = { {Fraction(2), Fraction(7), Fraction(4)} };
        
//         std::vector<std::vector<Fraction> > matrix; 
//         InitialMatrix(matrix_double, matrix);
//         std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
//         matrix.push_back(dependent_row[0]);
//         //Print2Dvector(matrix);

//         std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
//         std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
//         CheckMatrix(product, zeroVector(4));
//     }

//     SECTION("3rd Column Free"){
//         std::vector<std::vector<double> > matrix_double {{24, -12, 0, 12},
//                                                         {-6, 24, 0, -12},
//                                                         {12, 6, 0, -18}};
//         std::vector< std::vector<Fraction> > coefficient = { {Fraction(4), Fraction(5), Fraction(-1)} };

//         std::vector<std::vector<Fraction> > matrix; 
//         InitialMatrix(matrix_double, matrix);
//         std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
//         matrix.push_back(dependent_row[0]);
//         //Print2Dvector(matrix);

//         std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
//         std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
//         CheckMatrix(product, zeroVector(4));
//     }

//     SECTION("4th Column Free"){
//         std::vector<std::vector<double> > matrix_double {{-5, -3, 2, 4},
//                                                         {-10, -4, 6, 2},
//                                                         {-20, -6, 17, 0}};
//         std::vector< std::vector<Fraction> > coefficient = { {Fraction(2), Fraction(3), Fraction(2)} };

//         std::vector<std::vector<Fraction> > matrix; 
//         InitialMatrix(matrix_double, matrix);
//         std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
//         matrix.push_back(dependent_row[0]);
//         //Print2Dvector(matrix);

//         std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
//         std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
//         CheckMatrix(product, zeroVector(4));
//     }
// }
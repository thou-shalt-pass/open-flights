#include "tests_utilities.h"

#include "type.h"

#include "matrix_operation.h"

#include <iostream>

std::vector<std::vector<double>> TwoDim(const std::vector<double> matrix){
    std::vector< std::vector<double> > matrix2D;
    for(size_t i = 0; i < matrix.size(); i++){
        std::vector<double> row;
        row.push_back(matrix[i]);
        matrix2D.push_back(row);
    }
    return matrix2D;
}

void HelpTestMatrixOperator(const std::vector<double>& Solution, const std::vector<double>& Expected){
    double scalar = Solution[0] / Expected[0];
    for(size_t i = 1; i < Expected.size(); i++){
        REQUIRE(Solution[i] / Expected[i] == scalar);
    }
}

std::vector<std::vector<double>> zeroVector(size_t n){
    std::vector< std::vector<double> > zero_vector;
    for(size_t i = 0; i < n; i++){
        std::vector<double> row;
        row.push_back(0);
        zero_vector.push_back(row);
    }
    return zero_vector;
}

Matrix<double> Multiplication(const Matrix<double>& factor1, const Matrix<double>& factor2){
  if( factor1[0].size() != factor2.size() ){
    throw std::runtime_error("width of first matrix does not match the height of the second matrix");
  }

  Matrix<double> product;
  for(size_t i = 0; i < factor1.size(); i++){
    std::vector<double> p;
    for(size_t j = 0; j < factor2[0].size(); j++){
      double sum = 0;
      for(size_t k = 0; k < factor1[0].size(); k++){
        sum = sum + factor1[i][k] * factor2[k][j];
      }
      p.push_back(sum);
    }
    product.push_back(p);
  }

  return product;
}

void CheckMatrix(const std::vector< std::vector<double> >& matrix1, const std::vector< std::vector<double> >& matrix2){
     REQUIRE(matrix1.size() == matrix2.size());
     REQUIRE(matrix1[0].size() == matrix2[0].size());

     for(size_t i = 0; i < matrix1.size(); i++){
        CheckVectorDouble(matrix1[i],matrix2[i], 1e-10);
     }
 }

TEST_CASE("FindOneDimNullSpaceByLU(const Matrix<double>& matrix)", "[find_1d_null_space]") {
    SECTION("2*2 Matrix"){
        Matrix<double> M { { double(-4), double(3)}, {double(4), double(-3)}};
        std::vector<double> Solution = FindOneDimNullSpaceByLU(M);
        std::vector<double> Expected {double(3), double(4)};
        HelpTestMatrixOperator(Solution, Expected);
    }

    SECTION("3*3 Matrix1"){
        Matrix<double> matrix {{2, 6, 10},
                                {2, 9, 13}};
        Matrix<double >coefficient = { {double(1), double(2)} }; 
        // Use coefficient to product one linearly dependent row base on n - 1 linearly independent row


        Matrix<double> dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        Matrix<double> matrix_cpy = matrix;

        std::vector<double> solution = FindOneDimNullSpaceByLU(matrix);
        std::vector< std::vector<double> > product = Multiplication(matrix_cpy, TwoDim(solution));
        CheckMatrix(product, zeroVector(3));
    }

    SECTION("3*3 Column Free"){
        Matrix<double> matrix {{3, 5, 7},
                               {-1, 4, 9}};
        Matrix<double >coefficient = { {double(4), double(6)} };

        Matrix<double> dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        Matrix<double> matrix_cpy = matrix;

        std::vector<double> solution = FindOneDimNullSpaceByLU(matrix);
        std::vector< std::vector<double> > product = Multiplication(matrix_cpy, TwoDim(solution));
        CheckMatrix(product, zeroVector(3));
    }

    SECTION("4*4 Column Free"){
        Matrix<double> matrix {{-5, -3, 2, 4},
                        {-10, -4, 6, 2},
                        {-20, -6, 17, 0}};
        Matrix<double> coefficient = { {double(2), double(3), double(2)} };

        Matrix<double> dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        Matrix<double> matrix_cpy = matrix;

        std::vector<double> solution = FindOneDimNullSpaceByLU(matrix);
        Matrix<double> product = Multiplication(matrix_cpy, TwoDim(solution));
        CheckMatrix(product, zeroVector(4));
    }

    SECTION("4*4 Column Free"){
        Matrix<double> matrix {{3, 4, 2, 49},
                        {1, 1, 4, 7},
                        {0, 9, 2, 0}};
        Matrix<double> coefficient = { {double(3), double(5), double(9)}};

        Matrix<double> dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        Matrix<double> matrix_cpy = matrix;

        std::vector<double> solution = FindOneDimNullSpaceByLU(matrix);
        Matrix<double> product = Multiplication(matrix_cpy, TwoDim(solution));
        CheckMatrix(product, zeroVector(4));
    }
}
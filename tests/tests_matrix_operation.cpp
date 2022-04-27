#include "tests_utilities.h"

#include "type.h"

#include "matrix_operation.h"

void InitialMatrix(const std::vector<std::vector<double> >& matrix_double, std::vector< std::vector<Fraction> >& matrix){
    for(size_t i = 0; i < matrix_double.size(); i++){
        std::vector<Fraction> row;
        for(size_t j = 0; j < matrix_double[i].size(); j++){
            row.push_back( Fraction(matrix_double[i][j]) );
        }
        matrix.push_back(row);
    }
}

std::vector<std::vector<Fraction>> TwoDim(std::vector<Fraction> matrix){
    std::vector< std::vector<Fraction> > matrix2D;
    for(size_t i = 0; i < matrix.size(); i++){
        std::vector<Fraction> row;
        row.push_back(matrix[i]);
        matrix2D.push_back(row);
    }
    return matrix2D;
}

std::vector<std::vector<Fraction>> zeroVector(size_t n){
    std::vector< std::vector<Fraction> > zero_vector;
    for(size_t i = 0; i < n; i++){
        std::vector<Fraction> row;
        row.push_back(0);
        zero_vector.push_back(row);
    }
    return zero_vector;
}

void CheckMatrix(const std::vector< std::vector<Fraction> >& matrix1, const std::vector< std::vector<Fraction> >& matrix2){
    REQUIRE(matrix1.size() == matrix2.size());
    REQUIRE(matrix1[0].size() == matrix2[0].size());

    for(size_t i = 0; i < matrix1.size(); i++){
        for(size_t j = 0; j < matrix1[0].size(); j++){
            REQUIRE(matrix1[i][j] == matrix2[i][j]);
        }
    }
}

TEST_CASE("One Dim Null Space 3 * 3"){
    SECTION("1st Column Free"){
        std::vector<std::vector<double> > matrix_double {{0, 6, 10},
                                                        {0, 12, 13}};
        std::vector< std::vector<Fraction> > coefficient = { {Fraction(-2), Fraction(1)} };
        
        std::vector<std::vector<Fraction> > matrix; 
        InitialMatrix(matrix_double, matrix);
        std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        //Print2Dvector(matrix);

        std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
        std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
        CheckMatrix(product, zeroVector(3));
    }

    SECTION("2nd Column Free"){
        std::vector<std::vector<double> > matrix_double {{1, 0, 10},
                                                        {0, 0, 27}};
        std::vector< std::vector<Fraction> > coefficient = { {Fraction(4), Fraction(3)} };
        
        std::vector<std::vector<Fraction> > matrix; 
        InitialMatrix(matrix_double, matrix);
        std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        //Print2Dvector(matrix);

        std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
        std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
        CheckMatrix(product, zeroVector(3));
    }

    SECTION("3rd Column Free"){
        std::vector<std::vector<double> > matrix_double {{2, 6, 10},
                                                        {2, 9, 13}};
        std::vector< std::vector<Fraction> > coefficient = { {Fraction(1), Fraction(2)} };
        
        std::vector<std::vector<Fraction> > matrix; 
        InitialMatrix(matrix_double, matrix);
        std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        //Print2Dvector(matrix);

        std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
        std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
        CheckMatrix(product, zeroVector(3));
    }
}

TEST_CASE("One Dim Null Space 4 * 4"){
    SECTION("1st Column Free"){
        std::vector<std::vector<double> > matrix_double {{0, 0, 1, 5},
                                                        {0, 4, 2, 3},
                                                        {0, 3, 0, 2}};
        std::vector< std::vector<Fraction> > coefficient = { {Fraction(3), Fraction(1), Fraction(5)} };
        
        std::vector<std::vector<Fraction> > matrix; 
        InitialMatrix(matrix_double, matrix);
        std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        //Print2Dvector(matrix);

        std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
        std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
        CheckMatrix(product, zeroVector(4));
    }

    SECTION("2nd Column Free"){
        std::vector<std::vector<double> > matrix_double {{1, 4, 1, 5},
                                                        {1, 4, 2, 3},
                                                        {0, 0, 8, 2}};
        std::vector< std::vector<Fraction> > coefficient = { {Fraction(2), Fraction(7), Fraction(4)} };
        
        std::vector<std::vector<Fraction> > matrix; 
        InitialMatrix(matrix_double, matrix);
        std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        //Print2Dvector(matrix);

        std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
        std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
        CheckMatrix(product, zeroVector(4));
    }

    SECTION("3rd Column Free"){
        std::vector<std::vector<double> > matrix_double {{24, -12, 0, 12},
                                                        {-6, 24, 0, -12},
                                                        {12, 6, 0, -18}};
        std::vector< std::vector<Fraction> > coefficient = { {Fraction(4), Fraction(5), Fraction(-1)} };

        std::vector<std::vector<Fraction> > matrix; 
        InitialMatrix(matrix_double, matrix);
        std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        //Print2Dvector(matrix);

        std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
        std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
        CheckMatrix(product, zeroVector(4));
    }

    SECTION("4th Column Free"){
        std::vector<std::vector<double> > matrix_double {{-5, -3, 2, 4},
                                                        {-10, -4, 6, 2},
                                                        {-20, -6, 17, 0}};
        std::vector< std::vector<Fraction> > coefficient = { {Fraction(2), Fraction(3), Fraction(2)} };

        std::vector<std::vector<Fraction> > matrix; 
        InitialMatrix(matrix_double, matrix);
        std::vector< std::vector<Fraction> > dependent_row = Multiplication(coefficient, matrix);
        matrix.push_back(dependent_row[0]);
        //Print2Dvector(matrix);

        std::vector<Fraction> solution = FindOneDimNullSpace(matrix);
        std::vector< std::vector<Fraction> > product = Multiplication(matrix, TwoDim(solution));
        CheckMatrix(product, zeroVector(4));
    }
}
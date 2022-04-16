#include "matrix_operation.h"

void rowSwap(std::vector<double>& row1, std::vector<double>& row2){
    std::vector<double> row_tmp = row1;
    row1 = row2;
    row2 = row_tmp;
}

void rowScale(std::vector<double>& row, double scalar){
    for(size_t i = 0; i < row.size(); i++){
        row[i] = row[i] * scalar;
    }
}

void rowEliminate(std::vector<double>& row1, std::vector<double>& row2, double scalar){
    for(size_t i = 0; i < row1.size(); i++){
        row1[i] = row1[i] - row2[i] * scalar;
    }
}

void PrintVector(std::vector<double> v){
    for(size_t i = 0; i < v.size(); i++){
       std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void Print2Dvector(Matrix<double>& matrix){
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[0].size(); j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout <<std::endl;
    }
}

std::vector<double> FindOneDimNullSpace(const Matrix<double>& matrix) {
    std::vector<double> solution;

    Matrix<double> matrix_cpy = matrix;
    size_t row = 0;
    size_t row_free;
    for(size_t col = 0; col < matrix_cpy[0].size(); ++col){
        size_t i = row;
        while(i != matrix_cpy.size()){
            if(matrix_cpy[i][col] != 0){
                break;
            }
            ++i;
        }

        //col does not have a pivot (a free variable)
        if(i == matrix_cpy.size()){
            row_free = col;
            continue;
        }

        rowSwap(matrix_cpy[i],matrix_cpy[row]);
        rowScale(matrix_cpy[row], 1 / matrix_cpy[row][col]);

        //Elimate the value at this column
        for(size_t y = 0; y < matrix_cpy.size(); ++y){
            if(y != row){
                double factor = matrix_cpy[y][col] / matrix_cpy[row][col];
                rowEliminate(matrix_cpy[y],matrix_cpy[row],factor);
            }
        }

        row++;
        if(row == matrix_cpy.size()){
            break;
        }
    }

    for(size_t row = 0; row < matrix_cpy.size(); ++row){
       if(row != row_free){
           solution.push_back((-1)* matrix_cpy[row][row_free]);
       }else{
           solution.push_back(1);
       }
    }

    return solution;
}

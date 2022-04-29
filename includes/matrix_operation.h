#ifndef _MATRIX_OPERATION_H
#define _MATRIX_OPERATION_H

// #include <cassert>
// #include <fstream>
// #include <iostream>
#include <tuple>

#include "type.h"

/**
 * @brief 
 * 
 * reference: CLRS
 * 
 * @tparam T 
 * @param mat_a sqare matrix that is able to perform LU decomposition
 * @return std::pair<Matrix<T>, Matrix<T> > 
 */
template <typename T>
std::pair<Matrix<T>, Matrix<T> > LUDecomposition(Matrix<T>& mat_a) {
    // assert( mat_a.size() == mat_a[0].size() );
    size_t n = mat_a.size();
    Matrix<T> mat_l(n, std::vector<T>(n, 0)), mat_u(n, std::vector<T>(n, 0));
    for (size_t i = 0; i < n; ++i) { mat_l[i][i] = 1; }
    for (size_t k = 0; k < n; ++k) {
        // printf("k = %d\n", k);
        mat_u[k][k] = mat_a[k][k];
        for (size_t i = k + 1; i < n; ++i) {
            mat_l[i][k] = mat_a[i][k] / mat_u[k][k];
            mat_u[k][i] = mat_a[k][i];
        }
        for (size_t i = k + 1; i < n; ++i) {
            for (size_t j = k + 1; j < n; ++j) {
                mat_a[i][j] = mat_a[i][j] - mat_l[i][k] * mat_u[k][j];
            }
        }
    }
    return std::make_pair(std::move(mat_l), std::move(mat_u));
}

template <typename T>
std::vector<T> FindOneDimNullSpaceByLU(Matrix<T>& mat_a) {
    // assert( mat_a.size() == mat_a[0].size() );
    size_t n = mat_a.size();
    // std::ofstream ofs_mat_a("mat_a");
    // for (size_t i = 0; i < n; ++i) {
    //     for (size_t j = 0; j < n; ++j) {
    //         ofs_mat_a << mat_a[i][j] << " ";
    //     }
    //     ofs_mat_a << "\n";
    // }
    Matrix<T> mat_l, mat_u;
    std::tie(mat_l, mat_u) = LUDecomposition(mat_a);
    // std::ofstream ofs_mat_l("mat_l");
    // for (size_t i = 0; i < n; ++i) {
    //     for (size_t j = 0; j < n; ++j) {
    //         ofs_mat_l << mat_l[i][j] << " ";
    //     }
    //     ofs_mat_l << "\n";
    // }
    // std::ofstream ofs_mat_u("mat_u");
    // for (size_t i = 0; i < n; ++i) {
    //     for (size_t j = 0; j < n; ++j) {
    //         ofs_mat_u << mat_u[i][j] << " ";
    //     }
    //     ofs_mat_u << "\n";
    // }
    std::vector<T> vec_x(n, 0);
    vec_x[n - 1] = 1;
    for (size_t i = n - 2; i < n; --i) {
        for (size_t j = i + 1; j < n; ++j) {
            vec_x[i] -= mat_u[i][j] * vec_x[j];
        }
        vec_x[i] /= mat_u[i][i];
    }
    return vec_x;
}

template <typename T>
void rowScale(std::vector<T>& row, T scalar) {
    for (size_t i = 0; i < row.size(); i++) {
        row[i] = row[i] * scalar;
    }
}

template <typename T>
void rowEliminate(std::vector<T>& row1, std::vector<T>& row2, T scalar) {
    for (size_t i = 0; i < row1.size(); i++) {
        row1[i] = row1[i] - row2[i] * scalar;
        if (std::abs(row1[i]) < 1e-10) {
            row1[i] = 0;
        }
    }
}

template <typename T>
std::vector<T> FindOneDimNullSpaceByGaussian(Matrix<T>& matrix) {
    // assert( matrix.size() == matrix[0].size() );

    size_t n = matrix.size();

    size_t row = 0;
    for (size_t col = 0; col < n - 1; ++col) {
        // printf("col = %d\n", col);

        rowScale(matrix[row], 1.0 / matrix[row][col]);

        //Elimate the value at this column
        for (size_t y = 0; y < n; ++y) {
            if (y != row) {
                double factor = matrix[y][col] / matrix[row][col];
                rowEliminate(matrix[y], matrix[row],factor);
            }
        }

        row++;
    }

    std::vector<double> solution;
    for(size_t row = 0; row < n - 1; ++row) {
        solution.push_back(-matrix[row][n - 1]);
    }
    solution.push_back(1);

    return solution;
}

#endif
#ifndef _MATRIX_OPERATION_H
#define _MATRIX_OPERATION_H

#include "type.h"
#include <iostream>

std::vector<double> FindOneDimNullSpace(const Matrix<double>& matrix, double error);

void rowSwap(std::vector<double>& row1, std::vector<double>& row2);

void rowScale(std::vector<double>& row, double scalar);

void rowEliminate(std::vector<double>& row1, std::vector<double>& row2, double scalar);

void Print2Dvector(Matrix<double>& matrix);

#endif
#include "matrix_operation.h"

void rowSwap(std::vector<Fraction>& row1, std::vector<Fraction>& row2){
    std::vector<Fraction> row_tmp = row1;
    row1 = row2;
    row2 = row_tmp;
}

void rowScale(std::vector<Fraction>& row, Fraction scalar){
    for(size_t i = 0; i < row.size(); i++){
        row[i] = row[i] * scalar;
    }
}

void rowEliminate(std::vector<Fraction>& row1, std::vector<Fraction>& row2, Fraction scalar){
    for(size_t i = 0; i < row1.size(); i++){
        row1[i] = row1[i] - row2[i] * scalar;
    }
}

void PrintVector(std::vector<Fraction> v){
    for(size_t i = 0; i < v.size(); i++){
       std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void Print2Dvector(Matrix<Fraction>& matrix){
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[0].size(); j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout <<std::endl;
    }
}

std::vector<Fraction> FindOneDimNullSpace(const Matrix<double>& matrix) {
    std::vector<Fraction> solution;

    Matrix<Fraction> matrix_cpy;
    for(size_t row = 0; row < matrix.size(); row++){
        std::vector<Fraction> row_entries;
        for(size_t col = 0; col < matrix[0].size(); col++){
            row_entries.push_back(matrix[row][col]);
        }
        matrix_cpy.push_back(row_entries);
    }

    size_t row = 0;
    size_t row_free;
    for(size_t col = 0; col < matrix_cpy[0].size(); ++col){
        size_t i = row;
        while(i != matrix_cpy.size()){
            if(matrix_cpy[i][col].numerator != 0){
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
        rowScale(matrix_cpy[row], matrix_cpy[row][col].FindInverse());

        //Elimate the value at this column
        for(size_t y = 0; y < matrix_cpy.size(); ++y){
            if(y != row){
                Fraction factor = matrix_cpy[y][col] / matrix_cpy[row][col];
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
           Fraction tmp(-1);
           solution.push_back(tmp * matrix_cpy[row][row_free]);
       }else{
           solution.push_back(Fraction(1));
       }
    }
    
    return solution;
}

Fraction::Fraction(){
    numerator = 0;
    denominator = 1000;
}

//Precision of three decimals
Fraction::Fraction(double v){
    numerator = v * 1000;
    denominator = 1000;
    Valid();
    reduction();
}

Fraction::Fraction(int n, int d){
    numerator = n;
    denominator = d;
    Valid();
    reduction();
}

void Fraction::Fraction::Valid(){
    int maxvalue_int = std::numeric_limits<int>::max();
    if(denominator == 0){
        numerator = maxvalue_int;
        denominator = 1;
    }
}

int FindGCD(int a, int b){
    if(a == 0){
       return b;
    }
    if(b == 0){
        return a;
    }

    int r = a % b;
    return FindGCD(b,r);
}

void Fraction::reduction(){
    int gcd = FindGCD(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}

Fraction Fraction::FindInverse(){
    int new_numerator = denominator;
    int new_denominator = numerator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

std::string Fraction::toString() const{
    if(denominator == 1){
        return std::to_string(numerator);
    }else{
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
}

std::ostream& operator << (std::ostream& os,Fraction f){
    os << f.toString();
    return os;
}

bool operator== (const Fraction& f1, const Fraction& f2){
    return (f1.numerator / f1.denominator == f2.numerator / f2.denominator);
}

Fraction operator+ (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator- (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator* (const Fraction& f1, const Fraction& f2){
    int new_numerator = f1.numerator * f2.numerator;
    int new_denominator = f1.denominator * f2.denominator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}

Fraction operator/ (const Fraction& f1, const Fraction& f2){
     int new_numerator = f1.numerator * f2.denominator;
    int new_denominator = f1.denominator * f2.numerator;
    Fraction new_fraction(new_numerator,new_denominator);
    new_fraction.Valid();
    new_fraction.reduction();
    return new_fraction;
}
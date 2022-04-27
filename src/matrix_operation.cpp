#include "matrix_operation.h"
#include <stdexcept>

/*
void Print2Dvector(Matrix<Fraction>& matrix){
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[0].size(); j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout <<std::endl;
    }
}

void PrintSolution(std::vector<Fraction> solution){
    std::cout << "Print solution" <<std::endl;
    for(size_t i = 0; i < solution.size(); i++){
       std::cout << solution[i] << " ";
    }
    std::cout << std::endl;
}
*/

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

Matrix<Fraction> Multiplication(Matrix<Fraction> factor1, Matrix<Fraction> factor2){
  if( factor1[0].size() != factor2.size() ){
    throw std::runtime_error("width of first matrix does not match the height of the second matrix");
  }

  Matrix<Fraction> product;
  for(size_t i = 0; i < factor1.size(); i++){
    std::vector<Fraction> p;
    for(size_t j = 0; j < factor2[0].size(); j++){
      Fraction sum = 0;
      for(size_t k = 0; k < factor1[0].size(); k++){
        sum = sum + factor1[i][k] * factor2[k][j];
      }
      p.push_back(sum);
    }
    product.push_back(p);
  }

  return product;
}

std::vector<Fraction> FindOneDimNullSpace(const std::vector<std::vector <Fraction> >& matrix){
    std::vector<Fraction> solution;

    std::vector<std::vector <Fraction> > matrix_cpy(matrix);

    size_t free_variable_column;
    size_t row = 0;
    for(size_t col = 0; col < matrix_cpy.size(); col++){

       bool free_variable = true;
       size_t pivot_row;
       for(size_t r = row; r < matrix_cpy.size(); r++){
           if(matrix_cpy[r][col].numerator != 0){
               free_variable = false;
               pivot_row = r;
               break;
           }
       }
        
       if(free_variable){
           free_variable_column = col;
           //std::cout << "Free Variable at " << free_variable_column << std::endl;
           continue;
        }


        rowSwap(matrix_cpy[row],matrix_cpy[pivot_row]);
        rowScale(matrix_cpy[row], matrix_cpy[row][col].FindInverse());

        for(size_t y = 0; y < matrix_cpy.size(); y++){
            if(y != row && matrix_cpy[y][col].numerator != 0){
                Fraction factor ( matrix_cpy[y][col] / matrix_cpy[row][col] );
                rowEliminate(matrix_cpy[y], matrix_cpy[row], factor);
            }
        }

        row++;
    }

     //Eliminate the value at this column
    for(size_t y = 0; y < matrix_cpy.size(); ++y){
        if(y == free_variable_column){
          solution.push_back(1);
        }else if(matrix_cpy[y][y].numerator != 0){
            Fraction factor ( matrix_cpy[y][free_variable_column] / matrix_cpy[y][y]);
            factor = factor * (-1);
            solution.push_back(factor);
        }else{
          solution.push_back(0);
        }

    }

    //Print2Dvector(matrix_cpy);
    return solution;
}

/*
//Previous Version of FindOneDimNullSpace(general)
std::vector<Fraction> FindOneDimNullSpace(const Matrix<Fraction>& matrix) {
    std::vector<Fraction> solution;

    Matrix<Fraction> matrix_cpy(matrix);

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
*/

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
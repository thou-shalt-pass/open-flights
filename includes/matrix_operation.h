#ifndef _MATRIX_OPERATION_H
#define _MATRIX_OPERATION_H

#include "type.h"
#include <iostream>

class Fraction{
    public:
        /**
         * @brief Default Constructor for Fraction for value 0
         * Set numerator to 0 and denominator to 1000
         */
        Fraction();

        /**
         * @brief Construct a new Fraction object 
         * Set numerator to n and denominator to d
         * @param n value for numerator
         * @param d value for denominator
         */
        Fraction(int n , int d );

        /**
         * @brief Construct a new Fraction object with true value v 
         * three decimal precision
         * @param v the true value for the fraction
         */
        Fraction(double v);

        /**
         * @brief Find the Inverse of a Fraction (example: Inverse(3/10) --> 10/3 )
         * 
         * @return Fraction 
         */
        Fraction FindInverse();

        /**
         * @brief make a fraction valid
         * if the fraction's numerator and denominator are both 0, throw a runtime error
         * if the fraction's denominator is 0, set numerator to maximum value for int, and denominator to 1
         */
        void Valid();

        /**
         * @brief Reduce a fraction to lowest term 
         * example: 3/6 --> 1/2
         */
        void reduction();

        /**
         * @brief return a string containing the contents of a fraction
         * example: "5/6" 
         * @return a string containing the contents 
         */
        std::string toString() const;

        int numerator;
        int denominator;
    private:

};

/**
 * @brief Find the greatest common divisor for number a and b using Euclid's Algorithm
 * 
 * @param a 
 * @param b 
 * @return the greatest common divisor 
 */
int FindGCD(int a, int b);

/**
 * @brief << operator, use to_string function
 * 
 * @param os the stream to insert into 
 * @param f 
 * @return std::ostream& 
 */
std::ostream& operator << (std::ostream& os,Fraction f);

/**
 * @brief addition operator 
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator+ (const Fraction& f1, const Fraction& f2);

/**
 * @brief subtraction operator
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator- (const Fraction& f1, const Fraction& f2);

/**
 * @brief multiplication operator
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator* (const Fraction& f1, const Fraction& f2);

/**
 * @brief division operator 
 * 
 * @param f1 
 * @param f2 
 * @return Fraction 
 */
Fraction operator/ (const Fraction& f1, const Fraction& f2);

/**
 * @brief Comparision operator
 * 
 * @param f1 
 * @param f2 
 * @return true if f1.numerator/f1.denominator == f2.numerator/f2.denominator
 * @return false 
 */
bool operator== (const Fraction& f1, const Fraction& f2);

std::vector<Fraction> FindOneDimNullSpace(const Matrix<Fraction>& matrix);

/**
 * @brief matrix multiplication, throw an exception when multplication is not valid
 * 
 * @param factor1 
 * @param factor2 
 * @return std::vector< std::vector<Fraction> > 
 */
std::vector< std::vector<Fraction> > Multiplication(std::vector< std::vector<Fraction> > factor1, std::vector< std::vector<Fraction> > factor2);

/**
 * @brief Swap row1 and row2
 * 
 * @param row1 
 * @param row2 
 */
void rowSwap(std::vector<Fraction>& row1, std::vector<Fraction>& row2);

/**
 * @brief scale row by scalar
 * 
 * @param row 
 * @param scalar 
 */
void rowScale(std::vector<Fraction>& row, double scalar);

/**
 * @brief Helper function to row elimination : row1 = row1 - row2 * scalar
 * 
 * @param row1 
 * @param row2 
 * @param scalar 
 */
void rowEliminate(std::vector<Fraction>& row1, std::vector<Fraction>& row2, Fraction scalar);

/*
void Print2Dvector(Matrix<Fraction>& matrix);

void PrintSolution(std::vector<Fraction> solution);
*/

#endif
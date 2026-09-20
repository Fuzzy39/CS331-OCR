#ifndef MATRIX_H
#define MATRIX_H

#include "abstractMatrix.h"
#include "vector.h"


template <typename T>
class Matrix : public AbstractMatrix<T> {
public:
    Matrix(int rows, int columns);
    void fillMatrix(std::vector<std::vector<T>>);
    
    // computations
    static Matrix<T> operator*(const Matrix<T>&, const Matrix<T>&);
    static Matrix<T> operator+(const Matrix<T>&, const Matrix<T>&);
    static Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&);
    static Matrix<T> transpose(const Matrix<T>&);

    // computations with matrix and vector
    static Matrix<T> operator*(const Matrix<T>&, const Vector<T>&);
    static Vector<T> operator*(const Vector<T>&, const Matrix<T>&);
    static Matrix<T> operator+(const Matrix<T>&, const Vector<T>&);
    static Matrix<T> operator-(const Matrix<T>&, const Vector<T>&);

private:
    std::vector<std::vector<T>> data;
    int rows;
    int columns;
};

#endif
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace ocr
{

    template <typename T>
    class Vector;

    template <typename T>
    class Matrix 
    {
    public:
        Matrix(int rows, int columns);
        void fillMatrix(std::vector<std::vector<T>>);
        
        // computations
        Matrix<T> operator*(const Matrix<T>& other) const;
        Matrix<T> operator+(const Matrix<T>& other) const;
        Matrix<T> operator-(const Matrix<T>& other) const;
        static Matrix<T> transpose(const Matrix<T>&);

        // computations with vector
        Matrix<T> operator*(const Vector<T>& other) const;
        Matrix<T> operator+(const Vector<T>& other) const;
        Matrix<T> operator-(const Vector<T>& other) const;

    private:
        std::vector<std::vector<T>> data;
        int rows;
        int columns;
    };
}

#endif
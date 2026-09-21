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
        void fill(std::vector<std::vector<T>>);
        
        // computations
        Matrix<T> operator*(const Matrix<T>& other) const;
        Matrix<T> operator+(const Matrix<T>& other) const;
        Matrix<T> operator-(const Matrix<T>& other) const;
        static Matrix<T> transpose(const Matrix<T>&);

        // overloaded computations with vector
        Matrix<T> operator*(const Vector<T>& other) const;
        Matrix<T> operator+(const Vector<T>& other) const;
        Matrix<T> operator-(const Vector<T>& other) const;

        int getRows() const;
        int getColumns() const;
        int getData() const;
    private:
        std::vector<std::vector<T>> data;
        int rows;
        int columns;
    };
}

#endif
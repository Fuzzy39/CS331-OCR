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
        virtual void fill(std::vector<std::vector<T>>);
        
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
        std::vector<std::vector<T>> getData() const;

        // flatten
        static Vector<T> flattenToVector(const Matrix<T>&);
    private:
        std::vector<std::vector<T>> data;
        int rows;
        int columns;
    };
}

#endif
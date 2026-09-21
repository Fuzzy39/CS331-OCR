#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#include "data_structures/matrix.h"

namespace ocr
{
    template <typename T>
    class Vector : public Matrix<T>
    {
    public:
        Vector(int size) : Matrix<T>(size, 1) {}

        using Matrix<T>::fill;
        void fill(std::vector<T>);

        // computations
        T operator*(const Vector<T>& other) const; // dot product
        Vector<T> operator+(const Vector<T>& other) const;
        Vector<T> operator-(const Vector<T>& other) const;
        static Vector<T> transpose(const Vector<T>&);
        
        using Matrix<T>::operator*;
        using Matrix<T>::operator+;
        using Matrix<T>::operator-;

        // flatten
        static Vector flattenToVector(const Matrix<T>&);
    };
}

#endif
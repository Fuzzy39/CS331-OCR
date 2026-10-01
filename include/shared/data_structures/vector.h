#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#include "data_structures/matrix.h"

using namespace std;
namespace ocr
{
    template <typename T>
    class Vector : public Matrix<T>
    {
    public:
        Vector(size_t size) : Matrix<T>(size, 1) {}

        void fill(vector<T>);

        // computations
        T operator*(const Vector<T>& other) const; // dot product
        Vector<T> operator+(const Vector<T>& other) const;
        Vector<T> operator-(const Vector<T>& other) const;
        static Vector<T> transpose(const Vector<T>&);
        
        using Matrix<T>::fill;
        using Matrix<T>::operator*;
        using Matrix<T>::operator+;
        using Matrix<T>::operator-;
    };
}

#endif
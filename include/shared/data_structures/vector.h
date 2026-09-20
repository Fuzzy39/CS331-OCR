#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#include "data_structures/matrix.h"

template <typename T>
class Vector {
public:
    Vector(int size);
    void fillVector(std::vector<T>);
    
    // computations
    Vector<T> operator*(const Vector<T>& other) const;
    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    static Vector<T> transpose(const Vector<T>&);

    // computations with matrix
    Vector<T> operator*(const Matrix<T>& other) const;
    Vector<T> operator+(const Matrix<T>& other) const;
    Vector<T> operator-(const Matrix<T>& other) const;

    // flatten
    static Vector flattenToVector(const Matrix<T>&);

private:
    std::vector<T> data;
    int size;
};

#endif
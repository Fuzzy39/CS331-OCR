#ifndef VECTOR_H
#define VECTOR_H
#include <vector>

#include "abstractMatrix.h"

template <typename T>
class Vector : public AbstractMatrix<T> {
public:
    Vector(int size);
    void fillVector(std::vector<T>);
    
    // computations
    static Vector operator*(const Vector<T>&, const Vector<T>&);
    static Vector operator+(const Vector<T>&, const Vector<T>&);
    static Vector operator-(const Vector<T>&, const Vector<T>&);
    static Vector transpose(const Vector<T>&);

    // flatten
    static Vector flattenToVector(const Matrix<T>&);

private:
    std::vector<T> data;
    int size;
};

#endif
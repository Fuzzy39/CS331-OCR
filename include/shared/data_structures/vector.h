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
    static Vector multiply(const Vector<T>&, const Vector<T>&);
    static Vector add(const Vector<T>&, const Vector<T>&);
    static Vector subtract(const Vector<T>&, const Vector<T>&);
    static Vector transpose(const Vector<T>&);

private:
    std::vector<T> data;

};

#endif
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
    static Vector multiply(Vector, Vector);
    static Vector add(Vector, Vector);
    static Vector subtract(Vector, Vector);
    static Vector transpose(Vector);

private:
    std::vector<T> data;

};

#endif
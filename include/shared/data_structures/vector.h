#ifndef VECTOR_H
#define VECTOR_H
#include <vector>

#include "abstractMatrix.h"

class Vector : public AbstractMatrix {
public:
    Vector(int size);
    void fillVector(std::vector<double>);
    
    // computations
    static Vector multiply(Vector, Vector);
    static Vector add(Vector, Vector);
    static Vector subtract(Vector, Vector);
    static Vector transpose(Vector);

private:

    std::vector<double> data;

};

#endif
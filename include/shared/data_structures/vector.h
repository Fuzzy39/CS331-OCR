#ifndef VECTOR_H
#define VECTOR_H

#include "abstractMatrix.h"

class Vector : public AbstractMatrix {
public:
    Vector(int size);
    
    // computations
    static Vector multiply(Vector, Vector);
    static Vector add(Vector, Vector);
    static Vector subtract(Vector, Vector);
    static Vector transpose(Vector);

    
};


#endif;
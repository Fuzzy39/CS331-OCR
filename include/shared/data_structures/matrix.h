#ifndef MATRIX_H
#define MATRIX_H

#include "abstractMatrix.h"
#include "vector.h"

class Matrix : public AbstractMatrix {
public:
    Matrix(int width, int height);
    
    // computations
    static Matrix multiply(Matrix, Matrix);
    static Matrix add(Matrix, Matrix);
    static Matrix subtract(Matrix, Matrix);
    static Matrix transpose(Matrix);

    // computations with matrix and vector
    static Matrix multiply(Matrix, Vector);
    static Vector multiply(Vector, Matrix);

    static Matrix add(Matrix, Vector);
    static Matrix subtract(Matrix, Vector);

};

#endif;
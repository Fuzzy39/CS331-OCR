#ifndef ABSTRACT_MATRIX_H
#define ABSTRACT_MATRIX_H

class AbstractMatrix {
public:
    AbstractMatrix(int width, int height);
    int getWidth();
    int getHeight();
private: 
    int width;
    int height;
};

#endif
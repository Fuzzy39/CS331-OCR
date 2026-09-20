#include <iostream>
#include "data_structures/abstractMatrix.h"

AbstractMatrix::AbstractMatrix(int width, int height) {
    this->width = width;
    this->height = height;
};

int AbstractMatrix::getWidth() {
    return this->width;
}

int AbstractMatrix::getHeight() {
    return this->height;
}


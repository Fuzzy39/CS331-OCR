#include <iostream>
#include "data_structures/abstractMatrix.h"

// Basic Abstract Matrix Data Type

int AbstractMatrix::getWidth() {
    return this->width;
}

int AbstractMatrix::getHeight() {
    return this->height;
}

int AbstractMatrix::getArea() {
    return this->area;
}

void AbstractMatrix::setArea(int a) {
    this->area = a;
}

void AbstractMatrix::setWidth(int w) {
    this->width = w;
    this->setArea(w * this->height);
}

void AbstractMatrix::setHeight(int h) {
    this->height = h;
    this->setArea(this->width * h);
}

int AbstractMatrix::getArea() {
    return this->width * this->height;
}



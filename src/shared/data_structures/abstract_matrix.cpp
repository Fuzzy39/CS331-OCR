#include <iostream>
#include "data_structures/abstractMatrix.h"

template <typename T>
int AbstractMatrix<T>::getWidth() {
    return this->width;
}

template <typename T>
int AbstractMatrix<T>::getHeight() {
    return this->height;
}

template <typename T>
int AbstractMatrix<T>::getArea() {
    return this->area;
}

template <typename T>
void AbstractMatrix<T>::setArea(int a) {
    this->area = a;
}

template <typename T>
void AbstractMatrix<T>::setWidth(int w) {
    this->width = w;
    this->setArea(w * this->height);
}

template <typename T>
void AbstractMatrix<T>::setHeight(int h) {
    this->height = h;
    this->setArea(this->width * h);
}


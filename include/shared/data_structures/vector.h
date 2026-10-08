#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>

#include "data_structures/matrix.h"

namespace ocr
{
    template <typename T>
    class Vector : public Matrix<T>
    {
    public:
        Vector(size_t size); // defined
        Vector(const std::initializer_list<T>& ref);
        Vector(const Matrix<T>& matrix); // implicit type conversion

        T& operator[](int idx); // defined
        T operator[](int idx) const; // const non-ref defined
        void fill(const std::vector<T>& vctr); // defined

        void transpose(); // defined
        static Vector<T> transpose(const Vector<T>&); // defined
        size_t getSize() const; // defined

    private:
        size_t size;
    };
}

// definitions since its a template class so pair it right under method declerations
template <typename T>
ocr::Vector<T>::Vector(size_t size) : ocr::Matrix<T>(1,size) {
    this->size = size;
}

template <typename T>
ocr::Vector<T>::Vector(const std::initializer_list<T>& ref) : ocr::Matrix<T>(1,ref.size()){
    this->size = ref.size();
    this->data = std::make_shared<std::vector<std::vector<T>>>(1, std::vector<T>{});
    for (const T& val : ref){
        (*(this->data))[0].push_back(val);
    }
}

template <typename T>
ocr::Vector<T>::Vector(const Matrix<T>& matrix) : ocr::Matrix<T>(matrix.getRows(), matrix.getColumns()) {
    if (matrix.getRows() != 1 && matrix.getColumns() != 1) {
        std::string error = "Unable to convert to vector of matrix " + std::to_string(matrix.getRows()) + " x " + std::to_string(matrix.getColumns()) + ". At least one dimension needs to be equal to 1.";
        throw std::logic_error(error);
    }
    this->size = matrix.getRows() * matrix.getColumns();
    this->data = std::make_shared<std::vector<std::vector<T>>>(matrix.getData());
}

template <typename T>
size_t ocr::Vector<T>::getSize() const {
    return this->size;
}

template <typename T>
T& ocr::Vector<T>::operator[](int idx) {
    if ((ocr::Matrix<T>::getRows() == 1 && (idx < 0 || idx >= ocr::Matrix<T>::getColumns())) || (ocr::Matrix<T>::getColumns() == 1 && (idx < 0 || idx >= ocr::Matrix<T>::getRows()))) {
        throw std::out_of_range("index " + std::to_string(idx) + " is out of range of size " + std::to_string(size));
    }
    if (ocr::Matrix<T>::getRows() == 1) {
        return (*(this->data))[0][idx];
    } else {
        return (*(this->data))[idx][0];
    }
}

template <typename T>
T ocr::Vector<T>::operator[](int idx) const {
    if ((ocr::Matrix<T>::getRows() == 1 && (idx < 0 || idx >= ocr::Matrix<T>::getColumns())) || (ocr::Matrix<T>::getColumns() == 1 && (idx < 0 || idx >= ocr::Matrix<T>::getRows()))) {
        throw std::out_of_range("index " + std::to_string(idx) + " is out of range of size " + std::to_string(size));
    }
    if (ocr::Matrix<T>::getRows() == 1) {
        return (*(this->data))[0][idx];
    } else {
        return (*(this->data))[idx][0];
    }
}

template <typename T>
void ocr::Vector<T>::fill(const std::vector<T>& vctr){
    if (vctr.size() != size){
        std::string error = "Error: expected " + std::to_string(size) + " elements but received " + std::to_string(vctr.size()) + " instead.";
        throw std::logic_error(error);
    }   
    
    for (int idx = 0; idx < size; idx++) {
        (*(this->data))[0][idx] = vctr[idx];
    }
}

// transposes self
template <typename T>
void ocr::Vector<T>::transpose() {
    size_t tmp = this->rows;
    this->rows = this->columns;
    this->columns = tmp;

    if (this->columns == 1){ // to vertical
        for (int idx = 1; idx < size; idx++) {
            (*(this->data)).push_back({(*(this->data))[0][idx]});
        }
        (*(this->data))[0] = {(*(this->data))[0][0]};
    } else { // to horizontal
        for (int idx = 1; idx < size; idx++) {
            (*(this->data))[0].push_back((*(this->data))[idx][0]);
            (*(this->data)) = {(*(this->data))[0]};
        }

    }
}

template <typename T>
ocr::Vector<T> ocr::Vector<T>::transpose(const Vector<T>& ref) {
    ocr::Vector<T> trspdVctr(ref.size);
    
    for (int idx = 0; idx < ref.size; idx++) {
        trspdVctr[idx] = ref[idx];
    }

    trspdVctr.transpose();
    return trspdVctr;
}

#endif
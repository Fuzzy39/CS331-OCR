#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <vector>
#include <stdexcept>

#include "data_structures/matrix.h"

using namespace std;
namespace ocr
{
    template <typename T>
    class Vector : public Matrix<T>
    {
    public:
        Vector(size_t size); // defined
        
        T& operator[](int idx); // defined
        T operator[](int idx) const; // const non-ref defined
        void fill(const vector<T>& vctr); // defined

        // computations
        T operator*(const Vector<T>& other) const;
        Vector<T> operator+(const Vector<T>& other) const;
        Vector<T> operator-(const Vector<T>& other) const;
        void transpose(); // defined
        static Vector<T> transpose(const Vector<T>&); 
        
        size_t getSize() const; // defined
        
        using Matrix<T>::operator*;
        using Matrix<T>::operator+;
        using Matrix<T>::operator-;
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
size_t ocr::Vector<T>::getSize() const {
    return this->size;
}

template <typename T>
T& ocr::Vector<T>::operator[](int idx) {
    if ((ocr::Matrix<T>::getRows() == 1 && (idx < 0 || idx >= ocr::Matrix<T>::getColumns())) || (ocr::Matrix<T>::getColumns() == 1 && (idx < 0 || idx >= ocr::Matrix<T>::getRows()))) {
        throw out_of_range("index " + to_string(idx) + " is out of range of size " + to_string(size));
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
        throw out_of_range("index " + to_string(idx) + " is out of range of size " + to_string(size));
    }
    if (ocr::Matrix<T>::getRows() == 1) {
        return (*(this->data))[0][idx];
    } else {
        return (*(this->data))[idx][0];
    }
}

template <typename T>
void ocr::Vector<T>::fill(const vector<T>& vctr){
    if (vctr.size() != size){
        string error = "Error: expected " + to_string(size) + " elements but received " + to_string(vctr.size()) + " instead.";
        throw logic_error(error);
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
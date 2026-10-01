#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;
namespace ocr
{
    template <typename T>
    class Vector;

    template <typename T>
    class Matrix 
    {
    public:
        Matrix(size_t rows, size_t columns);
        virtual void fill(const vector<vector<T>>& matrix);
        
        // computations
        Matrix<T> operator*(const Matrix<T>& other) const;
        Matrix<T> operator+(const Matrix<T>& other) const;
        Matrix<T> operator-(const Matrix<T>& other) const;
        static Matrix<T> transpose(const Matrix<T>&);

        // overloaded computations with vector
        Matrix<T> operator*(const Vector<T>& other) const;
        Matrix<T> operator+(const Vector<T>& other) const;
        Matrix<T> operator-(const Vector<T>& other) const;

        size_t getRows() const;
        size_t getColumns() const;
        vector<vector<T>> getData() const;

        // flatten
        static Vector<T> flattenToVector(const Matrix<T>&);
    private:
        unique_ptr<vector<vector<T>>> data;
        size_t rows;
        size_t columns;
    };
}

// definitions since its a template class so pair it right under method/data declerations

template <typename T>
ocr::Matrix<T>::Matrix(std::size_t rows, std::size_t cols) {
    this->rows = rows;
    this->columns = cols;
    this->data = make_unique<vector<vector<T>>>(rows, vector<int>(columns, T{})); // fill with default val
}    

template <typename T>
size_t ocr::Matrix<T>::getRows() const {
    return this->rows;
}

template <typename T>
size_t ocr::Matrix<T>::getColumns() const {
    return this->columns;
}

template <typename T>
void ocr::Matrix<T>::fill(const vector<vector<T>>& matrix) {
    (*(this->data))[0][0] = matrix[0][0];  
}

template <typename T>
vector<vector<T>> ocr::Matrix<T>::getData() const {
    return *(this->data); // return copy
}


#endif
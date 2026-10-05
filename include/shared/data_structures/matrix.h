#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;
namespace ocr
{
    template <typename T>
    class Vector;

    template <typename T>
    class Matrix 
    {
    public:
        Matrix(size_t rows, size_t columns); // defined
        void fill(const vector<vector<T>>& matrix); // defined
        
        // access
        Vector<T> operator[](int idx); // defined

        // computations
        Matrix<T> operator*(const Matrix<T>& other) const; 
        Matrix<T> operator+(const Matrix<T>& other) const;
        Matrix<T> operator-(const Matrix<T>& other) const;
        static Matrix<T> transpose(const Matrix<T>&);
        
        // overloaded computations with vector
        // Matrix<T> operator*(const Vector<T>& other) const;
        // Matrix<T> operator+(const Vector<T>& other) const;
        // Matrix<T> operator-(const Vector<T>& other) const;

        size_t getRows() const; // defined
        size_t getColumns() const; // defined
        vector<vector<T>> getData() const; // defined

        // flatten
        static Vector<T> flattenToVector(const Matrix<T>&);
    protected: // protected so vector class can access it
        shared_ptr<vector<vector<T>>> data;
        size_t rows;
        size_t columns;
    };
}

// definitions since its a template class so pair it right under method/data declerations

template <typename T>
ocr::Matrix<T>::Matrix(std::size_t rows, std::size_t cols) {
    this->rows = rows;
    this->columns = cols;
    this->data = make_shared<vector<vector<T>>>(rows, vector<T>(columns, T{})); // fill with default val
}    

template <typename T>
ocr::Vector<T> ocr::Matrix<T>::operator[](int idx) {
    if (idx < 0 || idx >= rows) {
        throw out_of_range("index " + to_string(idx) + " is out of range of size " + to_string(rows));
    }
    ocr::Vector<T> newVector = ocr::Vector<T>(columns);
    newVector.fill((*(this->data))[idx]);
    return newVector;
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
    // need to validate matrix dimensions to ensure it fits object rows/columns requirements
    // therefore, I can't just do *(this->data) = matrix
    if (matrix.size() != rows) {
        string error = "Error: expected " + to_string(rows) + " rows but received " + to_string(matrix.size()) + " instead.";
        throw logic_error(error);
    } 

    for (int row = 0; row < rows; row++){
        if (matrix[row].size() != columns) {
             string error = "Error: expected " + to_string(columns) + " columns but received " + to_string(matrix[row].size()) + " instead.";
        throw logic_error(error);
        }
        for (int col = 0; col < columns; col++) {
            (*(this->data))[row][col] = matrix[row][col];
        }
    }
}

template <typename T>
vector<vector<T>> ocr::Matrix<T>::getData() const {
    return *(this->data); // return copy
}

// template <typename T>
// ocr::Vector<T> ocr::Matrix<T>::flattenToVector(const Matrix<T>&) {
//     ocr::Vector<T> resVector<T>(row * columns);
// }

// template <typename T>
// ocr::Matrix<T> ocr::Matrix<T>::transpose(const Matrix<T>& ref) {
//     ocr::Matrix<T> newMatrix(ref.columns, ref.rows);
//     for (int row = 0 ; row < ref.rows ; row++){
//         for (int col = 0; col < ref.columns ; col++){
//             (*(newMatrix.getData()))[row][col] = (*(ref.getData()))[col][row];
//         }
//     }
// }

template <typename T>
ocr::Matrix<T> ocr::Matrix<T>::operator+(const ocr::Matrix<T>& other) const {
    // for now, matrices must be the same dimension
    if (other.getRows() != this->rows || other.getColumns() != this->columns){
        throw logic_error("vector dimensions do not match");
    }

    ocr::Matrix<T> resMtrx(this->rows, this->columns);
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++){
            resMtrx[row][col] = (*this)[row][col] + other[row][col];
        }
    }

    return resMtrx;
}

#endif
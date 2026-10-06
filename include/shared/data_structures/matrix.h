#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <initializer_list>
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
        Matrix(const initializer_list<initializer_list<T>>& ref); // defined

        void fill(const vector<vector<T>>& matrix); // defined

        // access
        Vector<T> operator[](int idx); // defined

        // set data
        void set(int row, int col, T val); // defined

        // computations
        Matrix<T> operator*(const Matrix<T>& other) const; // defined
        Matrix<T> operator+(const Matrix<T>& other) const; // defined
        Matrix<T> operator-(const Matrix<T>& other) const; // defined
        static Matrix<T> transpose(const Matrix<T>&); // defined

        size_t getRows() const; // defined
        size_t getColumns() const; // defined
        vector<vector<T>> getData() const; // defined

        // flatten
        static Vector<T> flattenToVector(const Matrix<T>&); // defined

        // visualize
        void visualize() const; // defined
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
ocr::Matrix<T>::Matrix(const initializer_list<initializer_list<T>>& ref) {
    this->rows = ref.size();
    size_t expected_col_size = ref.begin()->size();

    for (const initializer_list<T>& row : ref){
        if (row.size() != expected_col_size){
            throw logic_error("inconsistent matrix dimensions.");
        }
    }

    this->columns = expected_col_size;
    this->data = make_shared<vector<vector<T>>>();

    for (const initializer_list<T>& row : ref){
        (*(this->data)).push_back(row);
    }
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
void ocr::Matrix<T>::visualize() const {
    for (int row = 0; row < this->rows; row++){
        for (int col = 0; col < this->columns; col++){
            cout << (*(this->data))[row][col] << " ";
        }
        cout << "\n";
    }
}

template <typename T>
void ocr::Matrix<T>::set(int row, int col, T val){
    if ((row < 0 || row >= this->rows) ||
        (col < 0 || col >= this->columns)) {
        string error = " index of [" + to_string(row) + "][" + to_string(col) + "] is out of bounds of dimensions " + to_string(this->rows) + " x " + to_string(this->columns) + ".";
        throw out_of_range(error);
    }
    (*(this->data))[row][col] = val;
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

template <typename T>
ocr::Vector<T> ocr::Matrix<T>::flattenToVector(const Matrix<T>& other) {
    int total_size = other.getRows() * other.getColumns();
    ocr::Vector<T> resVector(total_size);
    for (int idx = 0; idx < total_size; idx++){
        resVector[idx] = (other.getData())[static_cast<int>(idx / other.getRows())][idx % other.getColumns()];
    }
    return resVector;
}

template <typename T>
ocr::Matrix<T> ocr::Matrix<T>::operator+(const ocr::Matrix<T>& other) const {
    // for now, matrices must be the same dimension
    if (other.getRows() != this->rows || other.getColumns() != this->columns){
        throw logic_error("vector dimensions do not match");
    }

    ocr::Matrix<T> resMtrx(this->rows, this->columns);
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++){
            T new_val = (*(this->data))[row][col] + other.getData()[row][col];
            resMtrx.set(row, col, new_val);
        }
    }

    return resMtrx;
}

template <typename T>
ocr::Matrix<T> ocr::Matrix<T>::operator-(const ocr::Matrix<T>& other) const {
    // for now, matrices must be the same dimension
    if (other.getRows() != this->rows || other.getColumns() != this->columns){
        throw logic_error("vector dimensions do not match");
    }

    ocr::Matrix<T> resMtrx(this->rows, this->columns);
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++){
            T new_val = (*(this->data))[row][col] - other.getData()[row][col];
            resMtrx.set(row, col, new_val);
        }
    }

    return resMtrx;
}

template <typename T>
ocr::Matrix<T> ocr::Matrix<T>::operator*(const ocr::Matrix<T>& other) const {
    // matrices can be different dimensions but still must be compatible
    if (this->columns != other.getRows()){
        string error = "Matrix dimensions of " + to_string(this->rows) + " x " +
            to_string(this->columns) + " and " + to_string(other.getRows()) + " x " +
            to_string(other.getColumns()) + " are not compatible.";
        throw logic_error(error);
    }

    ocr::Matrix<T> new_matrix(this->rows, other.getColumns());
    const vector<vector<T>> other_data = other.getData();

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < other.getColumns(); col++){
            T acc_value = 0;
            for (size_t idx = 0; idx < this->columns; idx++) {
                acc_value += (*(this->data))[row][idx] * other_data[idx][col];
            }
            new_matrix.set(row, col, acc_value);
        }
    }
    return new_matrix;
}

template <typename T>
ocr::Matrix<T> ocr::Matrix<T>::transpose(const ocr::Matrix<T>& other) {
    Matrix<T> transposed_matrix(other.getColumns(), other.getRows());

    for (int row = 0; row < other.getRows(); row++){
        for (int col = 0; col < other.getColumns(); col++){
            transposed_matrix.set(col,row,other.getData()[row][col]);
        }
    }

    return transposed_matrix;
}

#endif
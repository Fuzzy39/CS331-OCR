#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

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
        virtual void fill(vector<vector<T>>);
        
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
        vector<vector<T>> data;
        size_t rows;
        size_t columns;
    };
}

// definitions since its a template class so pair it right under method/data declerations

template <typename T>
ocr::Matrix<T>::Matrix(std::size_t rows, std::size_t cols) {
    this->rows = rows;
    this->columns = cols;
}    

template <typename T>
size_t ocr::Matrix<T>::getRows() const {
    return this->rows;
}

template <typename T>
size_t ocr::Matrix<T>::getColumns() const {
    return this->columns;
}



#endif
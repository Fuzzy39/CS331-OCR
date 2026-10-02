#include <iostream>
#include "data_structures/vector.h"
#include "data_structures/matrix.h"

int main(void) {

    // matrix tests

    // ocr::Matrix<int> max_matrix(3,4);
    // std::cout << max_matrix.getRows() << std::endl;

    // vector<int> row_1 = {1,2,3,4};
    // vector<int> row_2 = {4,5,6,6};
    // vector<int> row_3 = {7,8,9};

    // vector<vector<int>> my_matrix = {row_1, row_2, row_3};

    // max_matrix.fill(my_matrix);

    // std::cout << max_matrix.getData()[0][0] << std::endl;

    // // vector<int> row_4 = {10, 11, 12};
    // // my_matrix[0][0] = 10;
    // // std::cout << max_matrix.getData()[0][0] << std::endl;

    // ocr::Matrix<int> trpse = ocr::Matrix<int>::transpose(max_matrix);

    // vector tests

    ocr::Vector<int> max_vector(4);
    std::cout << "size is " << max_vector.getSize() << std::endl;

    // fill
    max_vector.fill({1,2,3,4});

    // get element
    std::cout << "the 2nd index value is " << max_vector[2] << "." << std::endl;
    std::cout << "rows " << max_vector.getRows() << " and columns " << max_vector.getColumns() << endl;

    // transpose self
    // max_vector.transpose();
    // max_vector.transpose();
    // max_vector.transpose();

    // create a new transposition vector
    ocr::Vector<int> transposed_vector = ocr::Vector<int>::transpose(max_vector);

    std::cout << "the 3rd index value is " << transposed_vector[3] << "." << std::endl;
    std::cout << "rows " << transposed_vector.getRows() << " and columns " << transposed_vector.getColumns() << endl;

    ocr::Vector<int> vector1(2);
    vector1.fill({1,2});

    ocr::Vector<int> vector2(2);
    vector2.fill({3,5});

    ocr::Vector<int> vector3 = vector1 - vector2;
    std::cout << "vector 3 idx 1 is " << vector3[1] << endl;

    return 0;
}



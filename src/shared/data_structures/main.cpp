#include <iostream>
#include "data_structures/vector.h"
#include "data_structures/matrix.h"

int main(void)
{

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

    // ocr::Vector<int> max_vector(4);
    // std::cout << "size is " << max_vector.getSize() << std::endl;

    // // fill
    // max_vector.fill({1,2,3,4});

    // // get element
    // std::cout << "the 2nd index value is " << max_vector[2] << "." << std::endl;
    // std::cout << "rows " << max_vector.getRows() << " and columns " << max_vector.getColumns() << endl;

    // // transpose self
    // // max_vector.transpose();
    // // max_vector.transpose();
    // // max_vector.transpose();

    // // create a new transposition vector
    // ocr::Vector<int> transposed_vector = ocr::Vector<int>::transpose(max_vector);

    // std::cout << "the 3rd index value is " << transposed_vector[3] << "." << std::endl;
    // std::cout << "rows " << transposed_vector.getRows() << " and columns " << transposed_vector.getColumns() << endl;

    // ocr::Vector<int> vector1(2);
    // vector1.fill({1,2});

    // ocr::Vector<int> vector2(2);
    // vector2.fill({3,5});

    // ocr::Vector<int> vector3 = vector1 - vector2;
    // std::cout << "vector 3 idx 1 is " << vector3[1] << endl;

    // more matrix tests

    ocr::Matrix<int> matrix_one(2, 2);
    ocr::Matrix<int> matrix_two(2, 2);

    std::vector<std::vector<int>> m1 = {{1, 2}, {3, 1}};
    std::vector<std::vector<int>> m2 = {{5, 2}, {7, 8}};

    matrix_one.fill(m1);
    matrix_two.fill(m2);

    ocr::Vector<int> my_vec = matrix_one[0];
    // std::cout << " 1 index is " << my_vec[0] << "." << std::endl;

    int val = matrix_one[0][0];
    // std::cout << " 1 0 index is " << val << "." << std::endl;

    ocr::Matrix<int> matrix_three = matrix_one * matrix_two;
    std::cout << " 0 0 index is " << matrix_three[0][0] << "." << std::endl;

    matrix_three.visualize();

    // transpose test

    ocr::Matrix<int>::transpose(matrix_three).visualize();

    ocr::Matrix<int> matrix_four(5, 2);
    matrix_four.fill({{1, 2}, {4, 5}, {6, 7}, {6, 7}, {3, 5}});

    ocr::Vector<int> matrix_to_vector = ocr::Matrix<int>::flattenToVector(matrix_four);
    matrix_to_vector.visualize();

    
    // more testing with vector and matrix-mix calculations


    // matrix * matrix gives vector

    ocr::Matrix<int> t1(1,3);
    ocr::Matrix<int> t2(3,6);

    t1.fill({{1,2,3}});
    t2.fill({{1,2,3,5,4,2},{2,34,5,1,2,5},{6,3,2,6,3,1}});

    ocr::Vector<int> t3 = t1 * t2;

    t3.visualize();

    // vector * vector gives matrix

    ocr::Vector<int> vv1(2);
    ocr::Vector<int> vv2(3);
    vv1.fill({1, 2});
    vv1.transpose();
    vv2.fill({3, 4, 5});

    ocr::Matrix<int> vector_vector_result = vv1 * vv2;

    if (vector_vector_result.getData() !=
        std::vector<std::vector<int>>{{3, 4, 5}, {6, 8, 10}}) {
        std::cerr << "Vector * vector matrix test failed.\n";
        return 1;
    }

    // vector * matrix gives vector

    ocr::Vector<int> vector_matrix_vector(2);
    vector_matrix_vector.fill({1, 2});
    ocr::Matrix<int> vector_matrix_vector_operand(2, 3);
    vector_matrix_vector_operand.fill({{3, 4, 5}, {6, 7, 8}});

    ocr::Vector<int> vector_matrix_vector_result =
        vector_matrix_vector * vector_matrix_vector_operand;

    if (vector_matrix_vector_result.getRows() != 1 ||
        vector_matrix_vector_result.getColumns() != 3 ||
        vector_matrix_vector_result.getData() !=
            std::vector<std::vector<int>>{{15, 18, 21}}) {
        std::cerr << "Vector * matrix vector test failed.\n";
        return 1;
    }



    // vector * matrix gives matrix

    ocr::Vector<int> vector_matrix_matrix(2);
    vector_matrix_matrix.fill({1, 2});
    vector_matrix_matrix.transpose();
    ocr::Matrix<int> vector_matrix_matrix_operand(1, 3);
    vector_matrix_matrix_operand.fill({{3, 4, 5}});

    ocr::Matrix<int> vector_matrix_matrix_result =
        vector_matrix_matrix * vector_matrix_matrix_operand;

    if (vector_matrix_matrix_result.getData() !=
        std::vector<std::vector<int>>{{3, 4, 5}, {6, 8, 10}}) {
        std::cerr << "Vector * matrix matrix test failed.\n";
        return 1;
    }



    // matrix * vector gives vector

    ocr::Matrix<int> matrix_vector_vector_operand(2, 3);
    matrix_vector_vector_operand.fill({{1, 2, 3}, {4, 5, 6}});
    ocr::Vector<int> matrix_vector_vector(3);
    matrix_vector_vector.fill({7, 8, 9});

    ocr::Vector<int> matrix_vector_vector_result =
        matrix_vector_vector_operand * ocr::Vector<int>::transpose(matrix_vector_vector);

    if (matrix_vector_vector_result.getRows() != 2 ||
        matrix_vector_vector_result.getColumns() != 1 ||
        matrix_vector_vector_result.getData() !=
            std::vector<std::vector<int>>{{50}, {122}}) {
        std::cerr << "Matrix * vector vector test failed.\n";
        return 1;
    }

    // matrix * vector gives matrix

    ocr::Matrix<int> matrix_vector_matrix_operand(2, 1);
    matrix_vector_matrix_operand.fill({{1}, {2}});
    ocr::Vector<int> matrix_vector_matrix(3);
    matrix_vector_matrix.fill({3, 4, 5});

    ocr::Matrix<int> matrix_vector_matrix_result =
        matrix_vector_matrix_operand * matrix_vector_matrix;

    if (matrix_vector_matrix_result.getData() !=
        std::vector<std::vector<int>>{{3, 4, 5}, {6, 8, 10}}) {
        std::cerr << "Matrix * vector matrix test failed.\n";
        return 1;
    }

    std::cout << "Vector and matrix mixed-operation tests passed.\n" << std::endl;

    // initialization list test
    ocr::Matrix<int> i1 = {{1,2},{3,4}};
    ocr::Matrix<int> i2 = {{5,6},{7,8}};

    i1.visualize();

    ocr::Matrix<int> i3 = i1 * i2;

    i3.visualize();

    ocr::Vector<int> v1 = {1,2,3,4};
    ocr::Vector<int> v2 = {4,5,1,5};

    ocr::Vector<int> v3 = v1 + v2;

    v3.visualize();

    return 0;
}

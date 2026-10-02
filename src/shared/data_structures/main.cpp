#include <iostream>
#include "data_structures/vector.h"
#include "data_structures/matrix.h"


int main(void) {
    ocr::Matrix<int> max_matrix(3,4);
    std::cout << max_matrix.getRows() << std::endl;

    vector<int> row_1 = {1,2,3,4};
    vector<int> row_2 = {4,5,6,6};
    vector<int> row_3 = {7,8,9};

    vector<vector<int>> my_matrix = {row_1, row_2, row_3};

    max_matrix.fill(my_matrix);

    std::cout << max_matrix.getData()[0][0] << std::endl;

    // vector<int> row_4 = {10, 11, 12};
    // my_matrix[0][0] = 10;
    // std::cout << max_matrix.getData()[0][0] << std::endl;


    return 0;
}

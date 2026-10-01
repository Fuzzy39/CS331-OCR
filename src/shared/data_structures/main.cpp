#include <iostream>
#include "data_structures/vector.h"
#include "data_structures/matrix.h"


int main(void) {
    ocr::Matrix<int> max_matrix(3,4);
    std::cout << max_matrix.getRows() << std::endl;
    return 0;
}

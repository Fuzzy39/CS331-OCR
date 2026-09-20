#include <iostream>
#include "main.h"
#include "data_structures/abstractMatrix.h"
#include "test.h"

using namespace std;

int main(void)
{
    cout<<"This is classify!\n";
    AbstractMatrix myMatrix(5,6);
    cout << myMatrix.getHeight() << endl;

    test();
    return 0;
}


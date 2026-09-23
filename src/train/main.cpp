#include <iostream>
#include "main.h"
#include <preprocessing/image.h>
#include <applications/digitClassifier.h>
using namespace ocr;

int main(void)
{
    std::cout<<"This is train!\n";
    func();
    // Dataset<Digit> data("data/emnist-digits-test-images-idx3-ubyte", "data/emnist-digits-test-labels-idx1-ubyte");
    
    // for(int i = 0; i<100; i++)
    // {
    //     Digit d =   data.getLabel(i);
    //     std::cout<<((int)d-(int)Digit::Zero)<<"\n";
    // }
    return 0;
}
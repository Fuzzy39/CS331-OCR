#include <iostream>
#include "test.h"

int main(void)
{
    std::cout<<"This is extract!\n";
    test();

    // I imagine:
    /*
        Dataset data("path/to/imagedata", "path/to/labeldata"); // We'd get these from command line arguments and check them probably.
        size_t index = 0;
        for(Image img : Dataset.getImages())
        {
            SomeStringbuilderOrSomething("path/to/images")<<index;
            img.writeToFile(SomeStringBuilderOrSomething.cstr());
            index++;
        }
    
    */
    return 0;
}
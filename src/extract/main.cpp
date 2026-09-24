#include <iostream>
#include <preprocessing/dataset.h>
#include <applications/digitClassifier.h>
using namespace ocr;

int main(void)
{
    std::cout<<"This is extract!\n";

    // What I would think this program should do:
    // Takes in a path to the folder or two paths to the files for the dataset, and optional arguments for output path and maximum number of images
    // Outputs a series of images from the dataset, with the filenames LabelX.png, where label is the label (zero, one, two, etc.) and X is the numbered instance of that label.
    // could work differently but that's my thought
    

    // I imagine:
    /*
        Dataset data("path/to/imagedata", "path/to/labeldata"); // We'd get these from command line arguments and check them probably.
        size_t index = 0;
        for(Image img : data.getImages())
        {
            SomeStringbuilderOrSomething("path/to/images")<<index;
            img.writeToFile(SomeStringBuilderOrSomething.cstr());
            index++;
        }
    
    */

    // temp
    try
    {
        Dataset<Digit> data("data/emnist-digits-test-images-idx3-ubyte", "data/emnist-digits-test-labels-idx1-ubyte");
        
        for(int i = 0; i<100; i++)
        {
            Digit d =   data.getLabel(i);
            std::cout<<((int)d-(int)Digit::Zero)<<"\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
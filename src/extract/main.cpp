#include <iostream>

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
    return 0;
}
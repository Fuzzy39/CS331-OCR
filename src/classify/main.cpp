#include <iostream>
#include "neural_network/neuralNetwork.h"
#include <string>
#include "preprocessing/dataset.h"
#include "applications/digitClassifier.h"
#include "data_structures/vector.h"
#include "preprocessing/image.h"

using namespace std;

int main(void)
{
    
    // Loading in the neural network from file
    ocr::NeuralNetwork<double> nn("../output/trained.ocrweights");

    // loading in testing data
    Dataset<Digit> testingData("../data/emnist-digits-test-images-idx3-ubyte", "../data/emnist-digits-test-labels-idx1-ubyte");

    // testing

    ocr::Image& image = testingData.getImage(90);
    unique_ptr<ocr::Vector<double>> imageVector = image.asFlatVector(ocr::Image::Format::Grayscale);

    const ocr::Digit& label = testingData.getLabel(90);

    ocr::Vector<double> output = nn.evaluate(*imageVector);

    cout << "Actual Label: " << static_cast<int>(label) << endl;
    cout << "-----------------------------" << endl;

    for (int i = 0; i < output.getSize(); i++) {
        std::cout << "Digit: " << i << " Probability: " << (output[i] * 100) << "%" << std::endl;
    }

    return 0;

}



#include <iostream>
#include "neural_network/neuralNetwork.h"
#include <string>
#include "preprocessing/dataset.h"
#include "applications/digitClassifier.h"
#include "data_structures/vector.h"
#include "preprocessing/image.h"
#include <filesystem>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image-path>\n";
        return 1;
    }
    
    // loading in the user-provided image

    std::string imagePath = argv[1];
    const std::string absolute_path = static_cast<std::string>(std::filesystem::current_path()) + "/" + imagePath;
    std::cout << "Loading image from: " << absolute_path << std::endl;
    
    ocr::Image image(absolute_path, 28, 28);
    std::cout << "Image loaded successfully." << std::endl;
    unique_ptr<ocr::Vector<double>> imageVector = image.asFlatVector(ocr::Image::Format::Grayscale);


    // Loading in the neural network from file
    ocr::NeuralNetwork<double> nn("../output/trained.ocrweights");
    ocr::Vector<double> output = nn.evaluate(*imageVector);

    int guessedDigitIndex = 0;
    for (int i = 1; i < output.getSize(); i++) {
        if (output[i] > output[guessedDigitIndex]) {
            guessedDigitIndex = i;
        }
    }

    cout << "-----------------------------" << endl;

    for (int i = 0; i < output.getSize(); i++) {
        std::cout << "Digit: " << i << " Probability: " << (output[i] * 100) << "%";
        if (i == guessedDigitIndex) {
            std::cout << " <-- Most likely";
        }
        std::cout << std::endl;
    }

    return 0;
}



// this file trains the neural network on the MNIST dataset
// and saves weights for classification

#include <iostream>
#include "ffTrain.h"
#include "main.h"
#include "neural_network/neuralNetwork.h"
#include <string>
#include <preprocessing/dataset.h>
#include <applications/digitClassifier.h>
#include "data_structures/vector.h"

int main(void)
{

    // * Loading in the MNIST dataset

    // training data set
    Dataset<Digit> trainingData("../data/train-images.idx3-ubyte", "../data/train-labels.idx1-ubyte");

    // // testing data set
    Dataset<Digit> testingData("../data/t10k-images.idx3-ubyte", "../data/t10k-labels.idx1-ubyte");
    
    // sanity check that data was loaded/parsed correctly
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Training Data Count: " << trainingData.getImageCount() << std::endl;
    std::cout << "Testing Data Count: " << testingData.getImageCount() << std::endl;
    std::cout << "--------------------------------------------\n" << std::endl;
        
    // * Creating a neural network

    std::cout << "Creating a Neural Network" << std::endl;

    // input: 784 (28x28 flattened image)
    // output: 10 (digits 0-9)
    // hidden layers: 64, 32

    ocr::NeuralNetwork<double> nn(784, 10, std::vector<size_t>({64, 32}));
    nn.randomizeNetwork();
    nn.print();

    // hyperparameters
    size_t batch_size = 30;
    double learning_rate = 0.001; // how fast we want our MNIST model to learn.

    ocr::FFTrain<double> trainMNIST(nn, trainingData, testingData, learning_rate, batch_size);
    
    trainMNIST.train(10);

    return 0;
}
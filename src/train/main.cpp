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
    std::cout << "Creating a Neural Network" << std::endl;
    ocr::NeuralNetwork<double> nn(5, 3, std::vector<size_t>({4}));
    nn.randomizeNetwork();
    // nn.print();

    // training data set
    Dataset<Digit> trainingData("../data/emnist-digits-train-images-idx3-ubyte", "../data/emnist-digits-train-labels-idx1-ubyte");

    // testing data set
    Dataset<Digit> testingData("../data/emnist-digits-test-images-idx3-ubyte", "../data/emnist-digits-test-labels-idx1-ubyte");
    
    // misc
    size_t batch_size = 30;
    double learning_rate = 0.05;

    ocr::FFTrain<double> trainMNIST(nn, trainingData, testingData, learning_rate, batch_size);
    
    // tests

    // sample output and target
    Vector<double> so = {3.2, -1.2, 0.4, -0.1, 4.1, 0.5, -2.0, 1.3, 2.8, 0.3};
    double st = 3;

    // test softmax

    ocr::Vector<double> softmax = trainMNIST.train(10, so, st);
    // for (size_t i = 0; i < 10; i++){
    //     std::cout << to_string(softmax[i]) << " ";
    // }
    // std::cout << std::endl;

    // test cost function

    std::cout << "Cost Function when target is..." << std::endl;
    std::cout << "4" << std::endl;
    trainMNIST.train(10, so, 4);

    std::cout << "3" << std::endl;
    trainMNIST.train(10, so, 3);

    std::cout << "0" << std::endl;
    trainMNIST.train(10, so, 0);

    std::cout << "6" << std::endl;
    trainMNIST.train(10, so, 6);




    return 0;
}
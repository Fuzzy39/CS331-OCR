// Implementation for a feedforward (FF) neural network training class

#ifndef FF_TRAIN_H
#define FF_TRAIN_H

#include "shared/neural_network/neuralNetwork.h"

template <typename T>
class FFTrain
{
private:
    NeuralNetwork<T>& network;
    ocr::Dataset<double>& trainingData;
    ocr::Dataset<double>& testingData;

    double learningRate;
    size_t batchSize;
 

public:
    FFTrain(NeuralNetwork<T>& network, ocr::Dataset<double>& trainingData, ocr::Dataset<double>& testingData, double learningRate, size_t batchSize);

    //returns test data loss after training for epochs epochs.
    ocr::Vector<double> train(int epochs);
    NeuralNetwork<T>& getNetwork();

private:
    // helper methods
    double lossFunction(const std::vector<T>& output, const std::vector<T>& target);
    void backpropagate(const std::vector<T>& input, const std::vector<T>& target);
    void updateWeightsAndBiases();
};


#endif
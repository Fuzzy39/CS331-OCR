// Implementation for a feedforward (FF) neural network training class

#ifndef FF_TRAIN_H
#define FF_TRAIN_H

#include "shared/neural_network/neuralNetwork.h"

template <typename T>
class FFTrain {
public:
    FFTrain(NeuralNetwork<T>& network, std::vector<std::vector<Batch<T>>>& batches, double learningRate, int epochs);
    void train();
private:
    NeuralNetwork<T>& network;
    std::vector<std::vector<Batch<T>>>& batches;
    double learningRate;
    int epochs;

    // helper methods
    double lostFunction(const std::vector<T>& output, const std::vector<T>& target);
    void backpropagate(const std::vector<T>& input, const std::vector<T>& target);
    void updateWeightsAndBiases();
    void feedForward(const std::vector<T>& input);
};


#endif
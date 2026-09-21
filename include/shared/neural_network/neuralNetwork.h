#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "layer.h"

// input count is flattened image size
// output count is number of classes (categories) for classification

template <typename T>
class NeuralNetwork {
public:
    NeuralNetwork(int inputCount, int outputCount, std::vector<int> hiddenLayerSizes);
    void initializeNetwork();

private:
    std::vector<Layer<T>> layers;
};

#endif
#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "layer.h"

// input count is flattened image size
// output count is number of classes (categories) for classification
namespace ocr
{
    template <typename T>
    class NeuralNetwork 
    {
    private:
        std::vector<Layer<T>> layers;
    public:
        // creates a network with all weights an biases as default values.
        NeuralNetwork(size_t inputCount, size_t outputCount, std::vector<size_t> hiddenLayerSizes);

        // File I/O
        NeuralNetwork(std::string pathname);

        // do not include file extension in pathname. It's provided for you.
        void writeToFile(std::string pathname);

        //initialize network with random weights
        void randomizeNetwork();

        // Print the network.
        void print();


        // evauluate the neural net for a given input.
        ocr::Vector<T> evaluate(ocr::Vector<T> input);

        // get the size of the input layer.
        size_t getInputSize();

        // get number of neurons in every hidden layer and the output layer, where index 0 is the first hidden layer.
        std::unique_ptr<std::vector<size_t>> getLayerSizes();

        // functions to Modify individual weights and biases in the neural net.

        // For these functions:
        // layer is the nth layer of the nueral net, where the first hidden layer is index 0.
        // neuron is the index into the given layer.
        T getBias(size_t layer, size_t neuron);
        void setBias(size_t layer, size_t neuron, T value);

        // neuronFrom is the index into the layer before this one, and neuronTo is the index in this layer.
        T getWeight(size_t layer, size_t neuronFrom, size_t neuronTo);
        void setWeight(size_t layer, size_t neuronFrom, size_t neuronTo, T weight);
    };
}

#endif
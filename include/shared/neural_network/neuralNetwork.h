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
        NeuralNetwork(int inputCount, int outputCount, std::vector<int> hiddenLayerSizes);

        NueralNetwork(std::string pathname);

        void writeToFile(std::string pathname);

        //create network with random weights
        void randomizeNetwork();

        
        ocr::Vector<double> evaluate(ocr::Vector<double> input);

        
    };
}

#endif
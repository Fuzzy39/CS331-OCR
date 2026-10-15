#pragma once
#include "neural_network/neuralNetwork.h"

template <typename T>
ocr::NeuralNetwork<T>::NeuralNetwork(size_t inputCount, size_t outputCount, std::vector<size_t> hiddenLayerSizes): layers()
{
    size_t layersCount = hiddenLayerSizes.size()+1;
    // create layerSizes as a vector of every layer size, including inputs and outputs.
    std::vector<size_t> layerSizes = hiddenLayerSizes; // the copy to a new variable is just for legibility.
    layerSizes.insert(0, inputCount);
    layerSizes.push_back(outputCount);


    for(int i = 0; i<layersCount; i++)
    {
        layers.emplace_back(layerSizes[i], layerSizes[i+1]);
    }
}

template <typename T>
ocr::NeuralNetwork<T>::NeuralNetwork(std::string pathname)
{
    throw std::logic_error("Not implemented.");
}

template <typename T>
void ocr::NeuralNetwork<T>::writeToFile(std::string pathname)
{
    throw std::logic_error("Not implemented.");
}

//create network with random weights
template <typename T>
void ocr::NeuralNetwork<T>::randomizeNetwork()
{
    for(Layer<T> layer : layers)
    {
        layer.randomizeLayer();
    }
}

template <typename T>
ocr::Vector<T> ocr::NeuralNetwork<T>::evaluate(ocr::Vector<T> input)
{
    // pass the vector through each layer until we get the output.
    ocr::Vector toReturn = input;
    for(Layer<T> layer : layers)
    {
        toReturn = layer.evaluate(toReturn);
    }

    // Check that the output vector is of the right size.
    assert(toReturn.size() == layers[layers.size()-1].getNeuronCount());

    return toReturn;
}

template <typename T>
size_t getInputSize()
{
    assert(layers.size()!=0); // a neural net should never have zero layers.
    return layers[0].getInputCount();
}

template <typename T>
std::unique_ptr<std::vector<size_t>> ocr::NeuralNetwork<T>::getLayerSizes()
{
    // Here we construct the vector of sizes from scratch.
    auto toReturn = std::make_unique<std::vector<size_t>>();
    for(Layer<T> layer : layers)
    {
        toReturn->push_back(layer.getNeuronCount());
    }
    return toReturn;
}

template <typename T>
T ocr::NeuralNetwork<T>::getBias(size_t layer, size_t neuron)
{
    // using at instead of [] to throw an exception if this is out of bounds.
    return layers.at(layer).getBiases().at(neuron);
}

template <typename T>
void ocr::NeuralNetwork<T>::setBias(size_t layer, size_t neuron, T value)
{
    layers.at(layer).getBiases().at(neuron) = value;
}

template <typename T>
T ocr::NeuralNetwork<T>::getWeight(size_t layer, size_t neuronFrom, size_t neuronTo)
{
    ocr::Matrix<T> weights& = layers.at(layer).getWeights();
    return weights.at(neuronTo).at(neuronFrom); // Row is the neuron in this layer, Column is the neuron in the previous index.   
}

template <typename T>
void ocr::NeuralNetwork<T>::setWeight(size_t layer, size_t neuronFrom, size_t neuronTo, T weight)
{
    ocr::Matrix<T> weights& = layers.at(layer).getWeights();
    weights.at(neuronTo).at(neuronFrom) = weight;
}
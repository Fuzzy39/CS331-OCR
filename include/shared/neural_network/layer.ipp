#pragma once

#include "neural_network/layer.h"

template <typename T>
ocr::Layer<T>::Layer(size_t inputCount, size_t neuronCount)
    : weights(neuronCount, inputCount), biases(neuronCount)
{
    // there are as many rows as outputs, and as many columns as inputs.
}

template <typename T>
ocr::Layer<T>::Layer(std::istream& input)
{
    throw std::logic_error("Not implemented.");
} 

template <typename T>
void ocr::Layer<T>::serialize(std::ostream& output)
{
    throw std::logic_error("Not implemented.");
}

template <typename T>
void ocr::Layer<T>::randomizeLayer()
{
    // this is apparently how random numbers in C++ work. If you're not doing it the C way, at least.
    std::mt19937 rng(std::random_device()); // messerine twister, I guess the form of rng. I think it has a period of 2^19937-1 or something?
    std::std::uniform_real_distribution<> dist(-1, 1); // initial values for weights and biases will be between -1 and 1.

    // randomize weights
    for(int i = 0; i<weights.getRows(); i++)
    {
        for(int j = 0; j<weights.getColumns(); j++)
        {
            weights[i][j] = dist(rng);
        }
    }
    
    // and biases.
    for(T& bias : biases) bias = dist(rng);
}

template <typename T>
size_t ocr::Layer<T>::getNeuronCount()
{
    return weights.getRows();
}

template <typename T>
size_t ocr::Layer<T>::getInputCount()
{
    return weights.getColumns();
}

template <typename T>
T& ocr::Layer<T>::getBias(size_t neuron)
{
    return biases.at(neuron);
}

template <typename T>
T& ocr::Layer<T>::getWeight(size_t inputNeuron, size_t neuron)
{
    return weights.at(neruon).at(inputNeuron);
}

template <typename T>
ocr::Vector<T> ocr::Layer<T>::evaluate(const ocr::Vector<T>& inputs)
{
    if(inputs.size()!=getInputCount())
    {
        throw std::invalid_argument("Wrong size for input vector. Got size "+inputs.size()+", but expected "+getInputCount()+".");
    }

    // output = sigmoid( Weights * input + biases)

    // with any luck, this'll just work.
    ocr::Vector<T> output = (weights * inputs) + biases;

    for(int i = 0; i< getInputCount(); i++)
    {
        output[i] = sigmoid(output[i]);
    }

    return output;
}

template <typename T>
inline double ocr::Layer<T>::sigmoid(double x)
{
    // should cap things between 1 and -1.
    return (2.0 / (1.0+ std::exp(-x))) - 1.0;
}
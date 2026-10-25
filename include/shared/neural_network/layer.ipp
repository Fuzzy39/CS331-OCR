#pragma once

#include "neural_network/layer.h"
#include "FileUtil.h"
#include <random>
#include <string>

template <typename T>
ocr::Layer<T>::Layer(size_t inputCount, size_t neuronCount)
    : weights(neuronCount, inputCount), biases(neuronCount)
{
    // there are as many rows as outputs, and as many columns as inputs.
}

template <typename T>
ocr::Layer<T>::Layer(std::ifstream& input, size_t previousLayerNeurons, size_t layerSize) 
    : weights(layerSize, previousLayerNeurons), biases(layerSize)
{
    // read in weights from file.

    // It occurs to me you could probably do something mildly cursed like read the entirety of the weights at once,
    // then shove them into a std::vector and then construct the matrix that way.
    // I don't think there's a performance reason to prefer one over the other so I'll just keep this how I have it.
    for(int row = 0; row<weights.getRows(); row++)
    {
        for(int col = 0; col<weights.getColumns(); col++)
        {
            // We can't really make endianness assumptions since we don't know the type.
            // Also, I don't know how endianness works for doubles and floats.
            T weight = 0;
            // should probably do a static_cast or something here.
            input.read((char*)&weight, sizeof(T));
            weights.set(row, col, weight);
        }
    }

    // read in biases from file
    for(int i = 0; i<getNeuronCount(); i++)
    {
        T bias = 0;
        // should probably do a static_cast or something here.
        input.read((char*)&bias, sizeof(T));
        biases[i] = bias;
    }    

} 

template <typename T>
void ocr::Layer<T>::serialize(std::ofstream& output)
{
    // write the neuron size as described in weights file format.md
    FileUtil::writeInt<uint64_t>(output, getNeuronCount());

    // then, write the weights matrix to file.
    for(int row = 0; row<weights.getRows(); row++)
    {
        for(int col = 0; col<weights.getColumns(); col++)
        {
            output.write(reinterpret_cast<char*>(&weights[row][col]), sizeof(T));
        }
    }

    // finally, write the biases to the file.
    for(int i = 0; i<getNeuronCount(); i++)
    {
        output.write(reinterpret_cast<char*>(&biases[i]), sizeof(T));
    }

}

template <typename T>
void ocr::Layer<T>::print()
{
   std::cout<<"weights (Each row represents a neuron in this layer):\n";
   weights.visualize();
   std::cout<<"Biases:\n";
   biases.visualize();  
}


template <typename T>
void ocr::Layer<T>::randomizeLayer()
{
    // this is apparently how random numbers in C++ work. If you're not doing it the C way, at least.
    std::random_device dev;
    std::mt19937 rng(dev()); // messerine twister, I guess the form of rng. I think it has a period of 2^19937-1 or something?
    std::uniform_real_distribution<> dist(-1, 1); // initial values for weights and biases will be between -1 and 1.

    // randomize weights
    for(int i = 0; i<weights.getRows(); i++)
    {
        for(int j = 0; j<weights.getColumns(); j++)
        {
            weights.set(i, j, dist(rng));
        }
    }
    
    // and biases.
    for(size_t i = 0; i<biases.getSize(); i++)
    {
        biases[i]=dist(rng);
    }

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
T ocr::Layer<T>::getBias(size_t neuron)
{
    return biases[neuron];
}

template <typename T>
void ocr::Layer<T>::setBias(size_t neuron, T bias)
{
    biases[neuron] = bias;
} 


template <typename T>
T ocr::Layer<T>::getWeight(size_t inputNeuron, size_t neuron)
{
    return weights.getData().at(neuron).at(inputNeuron);
}

template <typename T>
void ocr::Layer<T>::setWeight(size_t inputNeuron, size_t neuron, T weight )
{
   weights.set(neuron, inputNeuron, weight);
}



template <typename T>
ocr::Vector<T> ocr::Layer<T>::evaluate(ocr::Vector<T>& inputs)
{
    if(inputs.getSize()!=getInputCount())
    {
        std::ostringstream error;
        error << "Wrong size for input vector. Got size " << inputs.getSize()
            <<", but expected " + std::to_string(getInputCount()) << ".";
        throw std::invalid_argument(error.str());
    }

    // output = sigmoid( Weights * input + biases)

    // with any luck, this'll just work. (Nope. I had to fix some things.)
    ocr::Vector<T> output = (weights * inputs.asColumn()) + biases.asColumn();

    for(int i = 0; i< getNeuronCount(); i++)
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
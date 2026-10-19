#pragma once
#include "neural_network/neuralNetwork.h"
#include "FileUtil.h"
#include <cassert>

template <typename T>
ocr::NeuralNetwork<T>::NeuralNetwork(size_t inputCount, size_t outputCount, std::vector<size_t> hiddenLayerSizes): layers()
{
    size_t layersCount = hiddenLayerSizes.size()+1;
    // create layerSizes as a vector of every layer size, including inputs and outputs.
    std::vector<size_t> layerSizes = hiddenLayerSizes; // the copy to a new variable is just for legibility.
    layerSizes.insert(layerSizes.begin(), inputCount);
    layerSizes.push_back(outputCount);


    for(int i = 0; i<layersCount; i++)
    {
        layers.emplace_back(layerSizes[i], layerSizes[i+1]);
    }
}

template <typename T>
ocr::NeuralNetwork<T>::NeuralNetwork(std::string pathname) : layers()
{
    // read the file and check that it's a weights file.
    std::ifstream file = FileUtil::openFileForRead(pathname);
    FileUtil::verifyMagicNumber(file, FileUtil::OCR_WEIGHTS_MAGIC, pathname);

    // read the remainder of the header
    size_t layerCount = FileUtil::readInt<size_t>(file);
    size_t previousLayerNeurons = FileUtil::readInt<size_t>(file);

    // then read each layer.
    for(int i = 0; i<layerCount; i++)
    {
        uint64_t neuronCount = FileUtil::readInt<uint64_t>(file);
        layers.emplace_back(Layer<T>(file, previousLayerNeurons, neuronCount));
        previousLayerNeurons = layers[i].getNeuronCount();
    }

      // I don't think you need to call close, since ifstream should clean up in its destructor. but it seems polite? Sure.
    file.close();
}

template <typename T>
void ocr::NeuralNetwork<T>::writeToFile(std::string pathname)
{
    pathname += ".ocrweights";
    std::ofstream file = FileUtil::openFileForWrite(pathname);

    // write the header: the magic number, then the number of layers, followed by the size of the input layer.
    FileUtil::writeInt<uint32_t>(file, FileUtil::OCR_WEIGHTS_MAGIC);
    FileUtil::writeInt<size_t>(file, layers.size());
    FileUtil::writeInt<size_t>(file, getInputSize());

    // then just write each layer.
    for(Layer<T> layer : layers)
    {
        layer.serialize(file);
    }
    file.close(); // pretty sure this is uneeded, but again, feels polite.
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
void ocr::NeuralNetwork<T>::print()
{
    int i = 0;
    for(Layer<T> layer : layers)
    {
        std::cout<<"layer "<<i<<" ("<<layer.getNeuronCount()<<" neurons):\n";
        layer.print();
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
    assert(toReturn.getSize() == layers[layers.size()-1].getNeuronCount());

    return toReturn;
}

template <typename T>
size_t ocr::NeuralNetwork<T>::getInputSize()
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
    return layers.at(layer).getBias(neuron);
}

template <typename T>
void ocr::NeuralNetwork<T>::setBias(size_t layer, size_t neuron, T value)
{
    layers.at(layer).setBias(neuron, value);
}

template <typename T>
T ocr::NeuralNetwork<T>::getWeight(size_t layer, size_t neuronFrom, size_t neuronTo)
{
    return layers.at(layer).getWeight(neuronFrom, neuronTo); // Row is the neuron in this layer, Column is the neuron in the previous index.   
}

template <typename T>
void ocr::NeuralNetwork<T>::setWeight(size_t layer, size_t neuronFrom, size_t neuronTo, T weight)
{
    layers.at(layer).setWeight(neuronFrom, neuronTo, weight);
}
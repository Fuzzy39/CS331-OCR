#pragma once
#include "neural_network/neuralNetwork.h"
#include "preprocessing/dataset.h"
#include "ffTrain.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <cmath>
#include <string>
#include "data_structures/vector.h"

using namespace std;

template <typename T>
ocr::FFTrain<T>::FFTrain(
    NeuralNetwork<T>& network, 
    ocr::Dataset<Digit>& trainingData, 
    ocr::Dataset<Digit>& testingData, 
    double learningRate, 
    size_t batchSize
) : network(network),  
    trainingData(trainingData),
    testingData(testingData),
    learningRate(learningRate),
    batchSize(batchSize)
{
};

// training functions

// before computing the cost function using categorical-cross-entropy,
// the output logits must be bounded by [0,1] and sum to 1.0.
// For example, an output of [1.4,-2.3,4.1,...] does not fit this criteria
// so, softmax converts these into positive values that add up to 1
// NOTE: larger logits grow towards one while smaller logits grow towards zero

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::softMax(const ocr::Vector<double>& output) {
    // first, need to find the max logit
    double maxLogit = numeric_limits<double>::lowest();
    for (size_t i = 0; i < output.getSize(); i++){
        maxLogit = max(maxLogit, output[i]);
    }   

    // normalize logits using formula e^(logit - max_logit)
    ocr::Vector<double> normalizedLogits(output.getSize());
    double normalizedLogitsTotal = 0.0;

    for (size_t i = 0; i < output.getSize(); i++) {
        double normalizedLogit = std::exp(output[i] - maxLogit);
        normalizedLogits[i] = normalizedLogit;
        normalizedLogitsTotal += normalizedLogit;
    }

    // now, normalize logits between [0,1]
    ocr::Vector<double> softMaxLogits(output.getSize());

    for (size_t i = 0; i < output.getSize(); i++) {
        softMaxLogits[i] = (normalizedLogits[i] / normalizedLogitsTotal);
    }

    return softMaxLogits;
}


// cost function (single training example)
// take model output function and compare against true target value

// template <typename T>
// double ocr::FFTrain<T>::costFunction(const ocr::Vector<T>& output, const T target) {

// }

// loss function (batches multiple training examples)
// template <typename T>
// vector<double> ocr::FFTrain<T>::lossFunction(const vector<T>& output, const vector<T>& target) {
    
// }

template <typename T>
ocr::Vector<double> FFTrain<T>::train(int epochs, ocr::Vector<double>& output, ocr::Vector<double>& target) {
    return this->softMax(output);
}


// getters

template <typename T>
NeuralNetwork<T>& ocr::FFTrain<T>::getNetwork() const {
    return this->network;
}

template <typename T>
double ocr::FFTrain<T>::getLearningRate() const {
    return this->learningRate;
}

template <typename T>
size_t ocr::FFTrain<T>::getBatchSize() const {
    return this->batchSize;
}
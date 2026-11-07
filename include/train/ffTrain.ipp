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

// include guards

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
// uses categorical cross entropy formula:
// L(y,y') = - (SUM from 0 to output size - 1) yi * ln(yi')
// where y is target and y' is predicted
// however, since 9/10 of yi values are 0.0, then this really reduces to:
// L(y, y') = -ln(y'c) where y'c is logit value at predicted index
template <typename T>
double ocr::FFTrain<T>::costFunction(const ocr::Vector<T>& output, const T target) {
    return (-1 * std::log(output[target]));
}

template <typename T>
ocr::Vector<double> FFTrain<T>::train(int epochs) {
    


}


// back propagation and gradient descent

template <typename T>
void ocr::FFTrain<T>::backPropagate(const ocr::Vector<T> &input, const ocr::Vector<T> &target) {

}

template <typename T>
void ocr::FFTrain<T>::updateWeights(const int layer, const ocr::Matrix<double>& weightDerivatives) {

}

template <typename T>
void ocr::FFTrain<T>::updateBiases(const int layer, const ocr::Matrix<double>& biasDerivatives) {

}

// gradient calculations

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::cceWRTpredicted(const ocr::Vector<double>& predicted, const T target) {

}

template <typename T>
ocr::Matrix<double> ocr::FFTrain<T>::cceWRTweights(const ocr::Vector<double>& outputErrorSignal, const ocr::Vector<double>& prevLayerActivationValues) {

}

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::cceWRTpla(const ocr::Matrix<double>& layerWeights, const ocr::Vector<double>& outputErrorSignal) {

}

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::layerErrorSignal(const ocr::Vector<double>& layerGradient, const ocr::Vector<double> preActivationLogits) {

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
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

#include "preprocessing/image.h"
#include "applications/digitClassifier.h"

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
    
    // ignore epochs for now
    // train on one image and label at a time, for now

    ocr::Image& testImage = this->testingData.getImage(0);
    unique_ptr<ocr::Vector<T>> testImageVector = testImage.asFlatVector(ocr::Image::Format::Grayscale);

    ocr::Digit& testLabel = this->testingData.getLabel(0);
    
    // evaluate forward pass
    ocr::Vector<T> output = this->network.evaluate(*testImageVector);
    output.visualize();
    // cout << "Softmax: " << this->softMax(output)->visualize() << endl;
    // cout << "Cost Function: " << this->costFunction(this->softMax(output), testLabel) << endl;




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
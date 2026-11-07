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
double ocr::FFTrain<T>::costFunction(const ocr::Vector<T>& output, const ocr::Digit target) {
    return (-1 * std::log(output[static_cast<int>(target)]));
}

template <typename T>
ocr::Vector<double> FFTrain<T>::train(int epochs) {
    
    // ignore epochs for now
    // train on one image and label at a time, for now

    ocr::Image& testImage = this->testingData.getImage(0);
    unique_ptr<ocr::Vector<T>> testImageVector = testImage.asFlatVector(ocr::Image::Format::Grayscale);

    const ocr::Digit& testLabel = this->testingData.getLabel(0);
    
    // evaluate forward pass
    ocr::Vector<T> output = this->network.evaluate(*testImageVector);
    
    // calculate the cost function
    double cost = this->costFunction(output, testLabel);
    cout << "Cost Function: " << cost << endl;

    // back prop
    this->backPropagate(output, testLabel);

}

// back propagation and gradient descent

template <typename T>
void ocr::FFTrain<T>::backPropagate(const ocr::Vector<T> &output, const ocr::Digit &target) {
    ocr::Vector<double> lastLayerOutputSignal = this->cceWRTpredicted(output, target);
    
    ocr::Matrix<double> lastLayerWeights = this->network.getLayer(this->network.getLayerSizes()->size() - 1).getWeights();
    ocr::Vector<double> lastLayerPla = this->cceWRTpla(lastLayerWeights, lastLayerOutputSignal);

    cout << " get cached logits for each layer" << endl;
    for (int i = 0; i < this->network.getLayerSizes()->size(); i++) {
        ocr::Vector<T> preActivationLogits = this->network.getPreActivationLogits(i);
        ocr::Vector<T> activationValues = this->network.getActivationValues(i);
        cout << "Layer " << i << " pre-activation logits: ";
        preActivationLogits.visualize();
        cout << "Layer " << i << " activation values: ";
        activationValues.visualize();
    }
    

}

template <typename T>
void ocr::FFTrain<T>::updateWeights(const int layer, const ocr::Matrix<double>& weightDerivatives) {

}

template <typename T>
void ocr::FFTrain<T>::updateBiases(const int layer, const ocr::Matrix<double>& biasDerivatives) {

}

// gradient calculations

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::cceWRTpredicted(const ocr::Vector<T>& predicted, const ocr::Digit target) {
    // y^ - y
    
    // create target vector, where all values are 0.0 besides target index of 1.0 
    ocr::Vector<double> targetVector = ocr::Vector<double>(predicted.getSize());
    targetVector.fill(std::vector<double>(predicted.getSize(), 0.0));
    targetVector[static_cast<int>(target)] = 1.0;

    ocr::Vector<T> predictedCopy = predicted;
    ocr::Vector<double> outputErrorSignal = predictedCopy.asColumn() - targetVector.asColumn();
    return outputErrorSignal;
}

template <typename T>
ocr::Matrix<double> ocr::FFTrain<T>::cceWRTweights(const ocr::Vector<double>& outputErrorSignal, const ocr::Vector<double>& prevLayerActivationValues) {

}

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::cceWRTpla(const ocr::Matrix<double>& layerWeights, const ocr::Vector<double>& outputErrorSignal) {
    ocr::Matrix<double> transposedLayerWeights = ocr::Matrix<double>::transpose(layerWeights);
    return transposedLayerWeights * outputErrorSignal;
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
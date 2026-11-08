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
    // train 100 images
    for (size_t i = 0; i < 100; i++) {
        cout << "Training on image " << i << endl;
        ocr::Image& image = this->trainingData.getImage(i);
        unique_ptr<ocr::Vector<T>> imageVector = image.asFlatVector(ocr::Image::Format::Grayscale);

        const ocr::Digit& label = this->trainingData.getLabel(i);
        
        // evaluate forward pass
        ocr::Vector<T> output = this->network.evaluate(*imageVector);

        // calculate the cost function
        double cost = this->costFunction(output, label);
        cout << "Cost Function for image " << i << ": " << cost << endl;

        // back prop
        this->backPropagate(*imageVector, output, label);
    }

    // save weights
    this->network.writeToFile("./output/trained.ocrweights");

}

// back propagation and gradient descent

template <typename T>
void ocr::FFTrain<T>::backPropagate(const ocr::Vector<T>& input, const ocr::Vector<T> &output, const ocr::Digit &target) { 
    
    // last layer
    ocr::Vector<double> lastLayerOutputSignal = this->cceWRTpredicted(output, target);
    
    ocr::Matrix<double> lastLayerWeights = this->network.getLayer(this->network.getLayerSizes()->size() - 1).getWeights();
    ocr::Vector<double> lastLayerPla = this->cceWRTpla(lastLayerWeights, lastLayerOutputSignal);

    // continue to back-propagate through the rest of the layers, starting from the second to last layer and moving backwards
    for (int layer_num = this->network.getLayerSizes()->size() - 2; layer_num >= 0; layer_num--) {

        // (step A) get incoming weight gradients across activation function
        ocr::Vector<double> currentErrorSignal = this->layerErrorSignal(lastLayerPla, layer_num);

        // (step B) compute weights gradient
        ocr::Matrix<double> currentLayerWeightGradients = this->cceWRTweights(currentErrorSignal, input, layer_num);

        // (Step C) compute bias gradient
        // not needed since it is directly equivalent to output error signal at layer l,
        // which is returned by layerErrorSignal

        // (Step D) pass gradient to next previous layer
        ocr::Matrix<double> currentLayerWeights = this->network.getLayer(layer_num).getWeights();
        ocr::Vector<double> nextLayerPla = this->cceWRTpla(currentLayerWeights, currentErrorSignal);

        // (Step E) update weights and biases for layer l

        // new weights (W[l] - learningRate * dC/dW[l])
        ocr::Matrix<double> subtractFrom = currentLayerWeightGradients * this->learningRate;    
        ocr::Matrix<double> newWeights = this->network.getLayer(layer_num).getWeights() - subtractFrom;
        this->network.getLayer(layer_num).updateWeights(newWeights);

        // new bias (b[l] - learningRate * dC/db[l])
        ocr::Vector<double> subtractFromBias = currentErrorSignal * this->learningRate;
        ocr::Vector<double> newBiases = this->network.getLayer(layer_num).getBiases().asColumn() - (subtractFromBias).asColumn();
        this->network.getLayer(layer_num).updateBiases(newBiases);

        // update lastLayerPla for next iteration
        lastLayerPla = nextLayerPla;
    }
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
ocr::Matrix<double> ocr::FFTrain<T>::cceWRTweights(const ocr::Vector<double>& outputErrorSignal, const ocr::Vector<double>& inputVctr, const size_t layer_num) {
    ocr::Vector<double> previousLayerActivationValues(10); // just a temp. placeholder
    if (layer_num > 0){
        previousLayerActivationValues = this->network.getActivationValues(layer_num - 1);
    } else { // input layer is activation values
        ocr::Vector<double> inputVctrCopy = inputVctr;
        previousLayerActivationValues = inputVctrCopy.asColumn(); 
    }
    ocr::Vector<double> outputErrorSignalCopy = outputErrorSignal;

    previousLayerActivationValues.transpose();
    return outputErrorSignalCopy.asColumn() * previousLayerActivationValues;
}

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::cceWRTpla(const ocr::Matrix<double>& layerWeights, const ocr::Vector<double>& outputErrorSignal) {
    ocr::Matrix<double> transposedLayerWeights = ocr::Matrix<double>::transpose(layerWeights);

    return transposedLayerWeights * outputErrorSignal;
}

template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::layerErrorSignal(const ocr::Vector<double>& layerGradient, const size_t layer_num) {
    ocr::Vector<double> sigmoidGrad = this->sigmoidGradient(layer_num);
    ocr::Vector<double> layerGradientCopy = layerGradient;
    return layerGradientCopy.asColumn() % sigmoidGrad.asColumn();
}   

// sigmoid gradient
template <typename T>
ocr::Vector<double> ocr::FFTrain<T>::sigmoidGradient(size_t layer) {
    // g'(z[l]) = a[l] * (1 - a[l]) 
    ocr::Vector<double> activationValues = this->network.getActivationValues(layer);
    
    // fill vector with 1.0 - a[l]
    std::vector<double> onesVctr(activationValues.getSize(), 1.0);
    ocr::Vector<double> ones(activationValues.getSize());
    ones.fill(onesVctr);
    ocr::Vector<double> oneMinusActivation = ones.asColumn() - activationValues.asColumn();

    return activationValues.asColumn() % oneMinusActivation.asColumn();
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
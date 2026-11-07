// Implementation for a feedforward (FF) neural network training class

#ifndef FF_TRAIN_H
#define FF_TRAIN_H

#include "neural_network/neuralNetwork.h"
#include <applications/digitClassifier.h>
#include "preprocessing/dataset.h"
#include "data_structures/vector.h"

namespace ocr
{
    template <typename T>
    class FFTrain
    {
    private:
        NeuralNetwork<T> &network;
        ocr::Dataset<Digit> &trainingData;
        ocr::Dataset<Digit> &testingData;

        double learningRate;
        size_t batchSize;

    public:
        FFTrain(NeuralNetwork<T> &network, ocr::Dataset<Digit> &trainingData, ocr::Dataset<Digit> &testingData, double learningRate, size_t batchSize);

        // returns test data loss after training for X epochs.
        ocr::Vector<double> train(int epochs);
        
        NeuralNetwork<T> &getNetwork() const;
        double getLearningRate() const;
        size_t getBatchSize() const;
        
    private:
        // helper methods
        ocr::Vector<double> softMax(const ocr::Vector<double>& output);
        double costFunction(const ocr::Vector<T>& output, const T target);
      
        void backPropagate(const ocr::Vector<T> &input, const ocr::Vector<T> &target);
        void updateWeights(const int layer, const ocr::Matrix<double>& weightDerivatives);
        void updateBiases(const int layer, const ocr::Matrix<double>& biasDerivatives);

        // gradient calculations
        // I wrote down where all of these came from (will send a scanned PDF), I understand most, but still sort of confusing lol

        // partial derivative of cce (cost function) with respect to logits, or predicted values
        // returns s^[l], the output error signal
        ocr::Vector<double> cceWRTpredicted(const ocr::Vector<double>& predicted, const T target);

        // partial derivative of cee (cost function) with respect to weights
        ocr::Matrix<double> cceWRTweights(const ocr::Vector<double>& outputErrorSignal, const ocr::Vector<double>& prevLayerActivationValues);

        // partial derivative of cce (cost function) with respect to bias
        // not needed since it is directly equivalent to output error signal at layer l,
        // which is returned by cceWRTpredicted

        // partial derivative of cce (cost function) with respect to previous layer's activation
        ocr::Vector<double> cceWRTpla(const ocr::Matrix<double>& layerWeights, const ocr::Vector<double>& outputErrorSignal);

        // calculate new S^[l] layer error signal where layer != L
        ocr::Vector<double> layerErrorSignal(const ocr::Vector<double>& layerGradient, const ocr::Vector<double> preActivationLogits);
    };
}

#include "ffTrain.ipp"

#endif
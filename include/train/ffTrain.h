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

        // returns test data loss after training for epochs epochs.
        ocr::Vector<double> train(int epochs, ocr::Vector<double>& output, double target);
        
        NeuralNetwork<T> &getNetwork() const;
        double getLearningRate() const;
        size_t getBatchSize() const;

    private:
        // helper methods
        ocr::Vector<double> softMax(const ocr::Vector<double>& output);
        double costFunction(const ocr::Vector<T>& output, const T target);
        // ocr::Vector<double> lossFunction(const ocr::Vector<T>& output, const ocr::Vector<T>& target);
        void backpropagate(const ocr::Vector<T> &input, const ocr::Vector<T> &target);
        void updateWeightsAndBiases();
    };
}

#include "ffTrain.ipp"

#endif
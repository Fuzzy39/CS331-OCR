#ifndef LAYER_H
#define LAYER_H

#include "data_structures/vector.h"
#include "data_structures/matrix.h"

template <typename T>
class Layer {
public:
    Layer(int neuronCount, int inputCount);
    
    // bias vector
    void initializeBiases();
    Vector<T> getBiases();

    // weight matrix
    void initializeWeights();
    Matrix<T> getWeights();

    // computations
    void computeOutput(const Vector<T>& inputs);
    void setOutputs(const Vector<T>& outputs);
    Vector<T> getOutputs();

private:
    int neuronCount;
    int inputCount;

    // weight matrix
    Matrix<T> weights;

    // bias
    Vector<T> biases;

    // layer outputs
    Vector<T> outputs;

};

#endif LAYER_H
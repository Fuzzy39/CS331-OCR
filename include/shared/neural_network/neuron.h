#ifndef NEURON_H
#define NEURON_H

#include "data_structures/vector.h"

template <typename T>
class Neuron {
public:
    Neuron(int numInputs);

    // Neuron weights
    Vector<T> getWeights();
    void setWeights(Vector<T> weights);

    // Neuron bias
    T getBias();
    void setBias(T bias);

    // output
    T getOutput();

    // Neuron activation function
    T activate(const Vector<T>& inputs);
  
private:
    int numInputs;
    Vector<T> weights;
    T bias;

    T output;
    void setOutput(T output);
};

# endif

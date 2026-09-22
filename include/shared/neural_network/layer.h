#ifndef LAYER_H
#define LAYER_H

#include "data_structures/vector.h"
#include "data_structures/matrix.h"

namespace ocr
{
    template <typename T>
    class Layer 
    {
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
        Vector<T> getOutputs();

    private:
        int neuronCount;
        int inputCount;

        Matrix<T> weights;
        Vector<T> biases;
        Vector<T> outputs;
    };
}
#endif
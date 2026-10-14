#ifndef LAYER_H
#define LAYER_H

#include "data_structures/vector.h"
#include "data_structures/matrix.h"

namespace ocr
{
    template <typename T>
    class Layer 
    {
    private:
        int neuronCount;
        int inputCount;

        Matrix<T> weights;
        Vector<T> biases;

    public:
        Layer(size_t neuronCount, size_t inputCount);
        void randomizeLayer();

        // bias vector
        Vector<T>& getBiases();

        // weight matrix
        Matrix<T>& getWeights();

        // computations
        Vector<T> evaluate(const Vector<T>& inputs);


    };
}
#endif
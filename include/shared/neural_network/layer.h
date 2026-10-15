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
        // each ROW represents weights that factor into a single output neuron.
        // each COLUMN reprsents weights that correspond to a single input neuron.
        // Meaning, each element, row, column, (i,j) is the weight from neuron j in the previous layer to the neuron i in this one.
        Matrix<T> weights;
        Vector<T> biases;

    public:
        Layer(size_t inputCount, size_t neuronCount);
        // for file io
        Layer(std::istream& input); // This may need additional parameters. Not 100% sure at present.
        void serialize(std::ostream& output);

        void randomizeLayer();

   
        // how big are we?
        size_t getNeuronCount();
        size_t getInputCount();


        // bias vector
        T& getBias(size_t neuron); 

        // weight matrix
        T& getWeight(size_t inputNeuron, size_t neuron);

        // computations
        Vector<T> evaluate(const Vector<T>& inputs);

        // How is a layer evaluated?
        // The following calulation is performed:
        // output = sigmoid( Weights * input + biases)
        // where: 
        //      input is a vector of size M
        //      output is a vector of size N
        //      weights is a matrix of N rows and, M columns, as described above.
        //      biases is a vector of size N
        //      and sigmoid is a function performed on each value in the output vector that serves to clamp the value between -1 and 1.

    private:
        static inline double sigmoid(double x);
    };
}
#endif
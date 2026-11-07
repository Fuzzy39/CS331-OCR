#ifndef LAYER_H
#define LAYER_H

#include "data_structures/vector.h"
#include "data_structures/matrix.h"
#include "neural_network/neuralNetwork.h"
namespace ocr
{   
    template<typename T>
    class NeuralNetwork;
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
        Layer(std::ifstream& input, size_t previousLayerSize, size_t layerSize);
        void serialize(std::ofstream& output);

        void randomizeLayer();

        void print();
   
        // how big are we?
        size_t getNeuronCount();
        size_t getInputCount();


        // bias vector
        ocr::Vector<T> getBiases();
        T getBias(size_t neuron);
        void setBias(size_t neuron, T bias); 

        // weight matrix
        ocr::Matrix<T> getWeights();
        T getWeight(size_t inputNeuron, size_t neuron);
        void setWeight(size_t inputNeuron, size_t neuron, T bias);

        

        // computations
        Vector<T> evaluate(Vector<T>& inputs, size_t layer_num, ocr::NeuralNetwork<T>& nn, bool lastLayer = false);

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
        static inline double softmax(double x, double sum);
    };
}

#include "layer.ipp"
#endif
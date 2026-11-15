#ifndef DIGIT_CLASSIFIER_H
#define DIGIT_CLASSIFIER_H

#include "preprocessing/dataset.h"
#include "neural_network/neuralNetwork.h"

namespace ocr
{
    enum class Digit
    {
        Zero = 0,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine
    };

    typedef Dataset<Digit> DigitDataSet;

    class DigitClassifier: public NeuralNetwork<double>
    {
        // Implement
        DigitClassifier(std::vector<int> hiddenLayerSizes);

        Digit evaluate(ocr::Vector<double> input);

    };
}

#endif
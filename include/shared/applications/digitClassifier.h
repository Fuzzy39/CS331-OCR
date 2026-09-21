#ifndef DIGIT_CLASSIFIER_H
#define DIGIT_CLASSIFIER_H

#include "preprocessing/dataset.h"
#include "preprocessing/batch.h"
#include "neural_network/neuralNetwork.h"

namespace ocr
{
    enum class Digit
    {
        Zero,
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
    typedef Batch<Digit> DigitBatch;

    class DigitClassifier: public NueralNetwork<double>
    {
        // Implement
    }
}

#endif
#ifndef BATCH_H
#define BATCH_H
#include "preprocessing/image.h"
#include "data_structures/vector.h"

template <typename T>
class Batch {
public:
    Batch(int batchSize, std::vector<Image> images, Vector<T> labels);

private:
    int batchSize;
    std::vector<Image> images;
    Vector<T> labels;
};


#endif
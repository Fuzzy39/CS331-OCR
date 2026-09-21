#ifndef BATCH_H
#define BATCH_H
#include "preprocessing/image.h"
#include "data_structures/vector.h"

namespace ocr
{
    template <typename enum T>
    class Batch 
    {
    private:
        size_t batchSize;
        std::vector<Image> images;
        Vector<T> labels;
    public:
        Batch(int batchSize, std::vector<Image> images, std::Vector<T> labels);

        size_t getSize();
        ocr::Image& getImage(size_t index);
        T getLabel(size_t index);
    
    };
}

#endif
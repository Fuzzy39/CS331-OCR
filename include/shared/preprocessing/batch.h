#ifndef BATCH_H
#define BATCH_H
#include "preprocessing/image.h"
#include "data_structures/vector.h"

namespace ocr
{
    template <typename T>
    class Batch 
    {
    private:
        // for reasons unknown to me, we can't name this type by name and have to make a typedef. Ok, sure.
        typedef typename std::vector<T>::iterator iterator;

        size_t batchSize;
        std::vector<Image>::iterator& images;
        iterator& labels;

    public:
        Batch(size_t batchSize, std::vector<Image>::iterator images, iterator labels);

        size_t getSize();
        ocr::Image& getImage(size_t index);
        T getLabel(size_t index);
    
    };
}

#endif
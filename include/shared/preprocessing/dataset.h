#ifndef DATASET_H
#define DATASET_H

#include "data_structures/vector.h"
#include "data_structures/matrix.h"
#include "preprocessing/image.h"
#include "preprocessing/batch.h"
#include <string>

using ocr::Image;
using ocr::Batch;

namespace ocr
{
    template <typename T>
    class Dataset
    {
    private:
        std::vector<Image> images;
        Vector<T> labels;
    public:
        Dataset(std::string imagePath, std::string labelPath);

        size_t getImageCount();

        // images
        Image& getImage(size_t index);
        std::vector<Image>& getAllImages();

        // labels
        Vector<T>& getLabel(size_t index);
        Vector<T>& getAllLabels();

        // batches
        std::unique_ptr<Batch<T>> getBatch(size_t index, size_t batchSize);
    };
}

#endif
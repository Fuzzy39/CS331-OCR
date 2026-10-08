#ifndef DATASET_H
#define DATASET_H

#include "data_structures/vector.h"
#include "data_structures/matrix.h"
#include "preprocessing/image.h"
#include "preprocessing/batch.h"
#include <string>
#include <vector>

using ocr::Image;
using ocr::Batch;

namespace ocr
{
   

    template <typename T>
    class Dataset
    {
    private:
        std::vector<std::unique_ptr<Image>> images;
        std::vector<T> labels;
    public:
        Dataset(std::string imagePath, std::string labelPath);

    private:
        void parseImages(std::string imagePath);
        void parseLabels(std::string labelPath);
        void verifyMagicNumber(std::ifstream& file, uint32_t expected, std::string filePath);
        uint32_t readIntFromFile(std::ifstream& file, std::string filePath);
    public:

        size_t getImageCount();

        // images
        Image& getImage(size_t index);
        std::vector<std::unique_ptr<Image>>& getAllImages();

        // labels
        T& getLabel(size_t index);
        Vector<T>& getAllLabels();

        // batches
        size_t getBatchCount(size_t batchSize);

        /// @brief gets the index(th) batch, where all batches (possibly except the last) are of size batchSize. 
        std::unique_ptr<Batch<T>> getBatch(size_t index, size_t batchSize);
    };
}

#include "preprocessing/dataset.ipp"
#endif
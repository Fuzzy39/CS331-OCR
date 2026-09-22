#pragma once
#include "preprocessing/dataset.h"
#include "preprocessing/batch.h"
using namespace ocr;

// implementation of the Dataset class

template <typename T>
Dataset<T>::Dataset(std::string imagePath, std::string labelPath)
{

}

template <typename T>
size_t Dataset<T>::getImageCount()
{
    return images.size();
}

// images
template <typename T>
Image& Dataset<T>::getImage(size_t index)
{
    // We use .at instread of the overloaded [] operator
    // so that the vector class throws an exception if index
    // is out of bounds.
    return images.at(index);
}

template <typename T>
std::vector<Image>& Dataset<T>::getAllImages()
{
    return images;
}

// labels
template <typename T>
T& Dataset<T>::getLabel(size_t index)
{
    // We use .at instread of the overloaded [] operator
    // so that the vector class throws an exception if index
    // is out of bounds.
    return labels.at(index);
}

template <typename T>
Vector<T>& Dataset<T>::getAllLabels()
{
    return labels;
}

template<typename T>
size_t getBatchCount(size_t batchSize)
{
    double number_of_batches = std::ceil(images.size()/static_cast<double>(batchSize));
    return static_cast<size_t>(number_of_batches);
}

// batches
template <typename T>
std::unique_ptr<Batch<T>> Dataset<T>::getBatch(size_t index, size_t batchSize)
{
    // this requires some implementation.

    if(index<0 || index>=getBatchCount(batchSize))
    {
        // Arguably we could depend on vector to throw an exception for us when we try to do something
        // wrong but given we're already putting some logic here we should probably be defensive instead.
        std::ostringstream error();
        error << "Dataset::getBatch: index: "<< index
              <<" is out of range for this dataset. Valid range is (0 - "<< getBatchCount(batchSize) <<".";

        throw std::out_of_range(error.str());
    }

    size_t image_index = index*batchSize;

    if(image_index+batchSize >= images.size())
    {
        // We will return a smaller batch if there's not quite enough entries.
        batchSize = images.size()-image_index;
    }

    // finally, create a new batch.
    return std::unique_ptr<Batch>(new Batch(batchsize, images.begin()+image_index, labels.begin()+image_index));
}
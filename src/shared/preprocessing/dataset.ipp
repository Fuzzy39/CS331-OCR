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

// batches
template <typename T>
std::unique_ptr<Batch<T>> Dataset<T>::getBatch(size_t index, size_t batchSize)
{
    // this requires some implementation.

    if(index<0 || index>=images.size())
    {
        // Arguably we could depend on vector to throw an exception for us when we try to do something
        // wrong but given we're already putting some logic here we should probably be defensive instead.
        std::ostringstream error();
        error << "Dataset::getBatch: index: "<< index
              <<" is out of range for this dataset. Valid range is (0 - "<< (images.size()-1)<<".";

        throw std::out_of_range(error.str());
    }

    if( index+batchSize >= images.size())
    {
        // We will return a smaller batch if there's not quite enough entries.
        batchSize = images.size()-index;
    }

    // create a new batch.
    // TODO: does the batch header need to be changed? should this logic go in Batch?
    return std::unique_ptr<Batch>(new Batch(batchsize, ))
}
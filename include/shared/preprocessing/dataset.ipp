#pragma once
#include "preprocessing/dataset.h"
#include "preprocessing/batch.h"
#include <fstream>
#include <iomanip>
#include <bit>
#include <memory>
#include <sstream>

using namespace ocr;


// implementation of the Dataset class

template <typename T>
ocr::Dataset<T>::Dataset(std::string imagePath, std::string labelPath): images(), labels()
{
    // Okay! So, we need to parse these dataset files into a buttload of images.
    /// delegate it!
    parseImages(imagePath);
    parseLabels(labelPath);

    if(images.size() != labels.size())
    {
        std::ostringstream error;
        error<<"Dataset::Dataset: Size mismatch between Images ("<<images.size()<<") and Labels ("<<labels.size()<<"). ";
        throw std::invalid_argument(error.str());
    }

}

template <typename T>
void ocr::Dataset<T>::parseImages(std::string imagePath)
{
    const uint32_t MNIST_IMAGE_MAGIC = 2051; // magic number for mnist image file.  

    // open the file for reading. Complain dramatically if something went wrong.
    std::ifstream file(imagePath.c_str(), std::ios::in | std::ios::binary);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit );

    if(!file.is_open() || file.fail())
    {
        std::ostringstream error;
        error<<"Dataset file at '"<<imagePath<<"' Could not be opened. Does the file exist?";
        throw std::invalid_argument(error.str());
    }

    // check that this file is actually supposed to be a label file.
    verifyMagicNumber(file, MNIST_IMAGE_MAGIC, imagePath);

    // Read the remainder of the header:
    uint32_t length    = readIntFromFile(file, imagePath);
    uint32_t pixelRows = readIntFromFile(file, imagePath);
    uint32_t pixelCols = readIntFromFile(file, imagePath);

    size_t imageBytes = pixelRows*pixelCols;
    char* imageData = new char[imageBytes];

    // Now, read the images from the file.
    for(int i = 0; i<length; i++)
    {
       

        file.read(imageData, sizeof(uint8_t)*imageBytes);

        if(file.eof())
        {
            std::ostringstream error;
            error<<"Unexpected end of file while reading from '"<<imagePath<<"'.";
            throw std::invalid_argument(error.str());
        }

        images.push_back(std::make_unique<Image>(pixelRows, pixelCols, Image::Format::Grayscale, imageData));

    }

    delete[] imageData;
    // I don't think you need to call close, since ifstream should clean up in its destructor. but it seems polite? Sure.
    file.close();
}


template <typename T>
void ocr::Dataset<T>::parseLabels(std::string labelPath)
{
    const uint32_t MNIST_LABEL_MAGIC = 2049; // magic number for mnist label file.
    const size_t BUFFER_SIZE = 100;    

    // open the file for reading. Complain dramatically if something went wrong.
    std::ifstream file(labelPath.c_str(), std::ios::in | std::ios::binary);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit );

    if(!file.is_open() || file.fail())
    {
        std::ostringstream error;
        error<<"Label file at '"<<labelPath<<"' Could not be opened. Does the file exist?";
        throw std::invalid_argument(error.str());
    }

    // check that this file is actually supposed to be a label file.
    verifyMagicNumber(file, MNIST_LABEL_MAGIC, labelPath);

    // Read the number of labels expected:

    uint32_t length = readIntFromFile(file, labelPath);
    
    // read through all of the labels the file claims will be there and 
    while(length > 0)
    {
        char buffer[BUFFER_SIZE];
        size_t bytesToRead = BUFFER_SIZE > length ? length: BUFFER_SIZE;

        file.read(&(buffer[0]), sizeof(uint8_t)*bytesToRead);
 
        if(file.eof())
        {
            std::ostringstream error;
            error<<"Unexpected end of file while reading from '"<<labelPath<<"'.";
            throw std::invalid_argument(error.str());
        }

        for(uint8_t labelData : buffer)
        {
            labels.push_back(static_cast<T>(labelData));
        }

        length -= bytesToRead;
    }

    // I don't think you need to call close, since ifstream should clean up in its destructor. but it seems polite? Sure.
    file.close();
}


template <typename T>
void ocr::Dataset<T>::verifyMagicNumber(std::ifstream& file, uint32_t expected, std::string filePath)
{
    // Many types of files contain magic numbers in their headers as a simple check for programs so that they know the file actually is supposed to be of the format they are parsing it as.
    // the dataset files have magic numbers, so we ought to check them.
    uint32_t magic_number = readIntFromFile(file, filePath);
    if(magic_number != expected)
    {
        std::ostringstream error;     
        error<<"Got wrong magic number for file at '"<<filePath<<
            "' (Got: 0x"<< std::hex << std::setw(8) << std::setfill('0')<<magic_number<<
            ", Expected: 0x"<<expected<<"). The file is malformed or of the wrong format.";
        throw std::invalid_argument(error.str());
    }
}


template <typename T>
uint32_t ocr::Dataset<T>::readIntFromFile(std::ifstream& file, std::string filePath)
{
    
    uint32_t toReturn = 0;
    file.read((char*)&toReturn, sizeof(uint32_t));

    if(file.eof())
    {
        file.close();
        std::ostringstream error;
        error<<"Unexpected end of file while reading from '"<<filePath<<"'.";
        throw std::invalid_argument(error.str());
    }

    if(std::endian::native == std::endian::little)
    {
        // swap the bits around if we're on x86 (I mean, Max has a mac I think so this could run on arm, right?)
        return std::byteswap<uint32_t>(toReturn);
    }

    return toReturn;
}


template <typename T>
size_t ocr::Dataset<T>::getImageCount()
{
    return images.size();
}

// images
template <typename T>
Image& ocr::Dataset<T>::getImage(size_t index)
{
    // We use .at instread of the overloaded [] operator
    // so that the vector class throws an exception if index
    // is out of bounds.
    return images.at(index);
}

template <typename T>
std::vector<std::unique_ptr<Image>>& ocr::Dataset<T>::getAllImages()
{
    return images;
}

// labels
template <typename T>
T& ocr::Dataset<T>::getLabel(size_t index)
{
    // We use .at instread of the overloaded [] operator
    // so that the vector class throws an exception if index
    // is out of bounds.
    return labels.at(index);
}

template <typename T>
Vector<T>& ocr::Dataset<T>::getAllLabels()
{
    return labels;
}

template<typename T>
size_t ocr::Dataset<T>::getBatchCount(size_t batchSize)
{
    double number_of_batches = std::ceil(images.size()/static_cast<double>(batchSize));
    return static_cast<size_t>(number_of_batches);
}

// batches
template <typename T>
std::unique_ptr<Batch<T>> ocr::Dataset<T>::getBatch(size_t index, size_t batchSize)
{
    // this requires some implementation.

    if(index<0 || index>=getBatchCount(batchSize))
    {
        // Arguably we could depend on vector to throw an exception for us when we try to do something
        // wrong but given we're already putting some logic here we should probably be defensive instead.
        std::ostringstream error;
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
    return make_unique<Batch>(batchSize, images.begin()+image_index, labels.begin()+image_index);
}
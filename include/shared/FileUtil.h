# pragma once
#include <fstream>
#include <cstdint>

namespace FileUtil
{
    extern const uint32_t MNIST_IMAGE_MAGIC; // magic number for mnist image file.  
    extern const uint32_t MNIST_LABEL_MAGIC; // magic number for mnist label file.
    extern const uint32_t OCR_WEIGHTS_MAGIC; // magic number for our weights file.

    // the way those lined up was extremely satisfying.

    // throws std::invalid_argument if the file doesn't exist. Sets up the stream to throw exceptions on failure. (std::ios_base::failure)?
    std::ifstream openFileForRead(std::string path);

    // throws std::invalid_argument if the file can't be opened. Sets up the stream ot thow exceptions on failure. (std::ios_base::failure)?
    std::ofstream openFileForWrite(std::string path);

    // Many types of files contain magic numbers in their headers as a simple check for programs so that they know the file actually is supposed to be of the format they are parsing it as.
    // the dataset files have magic numbers, so we ought to check them.
    void verifyMagicNumber(std::ifstream& file, uint32_t expected, std::string filePath);

    // read or write an int of the given type, converting for endianess.
    template <typename intType> intType readInt(std::ifstream& file);
    template <typename intType> void writeInt(std::ofstream& file, intType toWrite);
}

#include "FileUtil.ipp"
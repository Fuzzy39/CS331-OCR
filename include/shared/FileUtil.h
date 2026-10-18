# pragma once
#include <fstream>
#include <cstdint>

namespace FileUtil
{

    // throws invalid_argument if the file doen't exist. Sets up the stream to throw exceptions on failure.
    std::ifstream openFileForRead(std::string path);

    // probably also throws stuff.
    std::ofstream openFileForWrite(std::string path);

    void verifyMagicNumber(std::ifstream& file, uint32_t expected, std::string filePath);

    template <typename intType>
    intType readInt(std::ifstream& file);

    template <typename intType>
    void writeInt(std::ofstream& file, intType toWrite);
}
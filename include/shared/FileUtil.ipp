#pragma once
#include "FileUtil.h"
#include <iomanip>

const uint32_t FileUtil::MNIST_IMAGE_MAGIC = 2051; // magic number for mnist image file.  
const uint32_t FileUtil::MNIST_LABEL_MAGIC = 2049; // magic number for mnist label file.
const uint32_t FileUtil::OCR_WEIGHTS_MAGIC = 0x0C40; // magic number for our weights file.

std::ifstream FileUtil::openFileForRead(std::string path)
{
    // open the file for reading. Complain dramatically if something went wrong.
    std::ifstream toReturn(path.c_str(), std::ios::in | std::ios::binary);
    
    if(!toReturn.is_open() || toReturn.fail())
    {
        std::ostringstream error;
        error<<"File at '"<<path<<"' Could not be opened. Does the file exist?";
        throw std::invalid_argument(error.str());
    }
    toReturn.exceptions(std::ifstream::failbit | std::ifstream::badbit );

    return toReturn;
}

std::ofstream FileUtil::openFileForWrite(std::string path)
{
    // trunc should, I think, delete the contents of the file if there was anything here before.
    // The file should also be created if it doesn't exist.
    std::ofstream toReturn(path.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    if(!toReturn.is_open() || toReturn.fail())
    {
        std::ostringstream error;
        error<<"File at '"<<path<<"' Could not be opened. Does the path to the file exist?";
        throw std::invalid_argument(error.str());
    }
    toReturn.exceptions(std::ifstream::failbit | std::ifstream::badbit );

    return toReturn;

}


void FileUtil::verifyMagicNumber(std::ifstream& file, uint32_t expected, std::string filePath)
{
    uint32_t magic_number = FileUtil::readInt<uint32_t>(file);
    if(magic_number != expected)
    {
        std::ostringstream error;     
        error<<"Got wrong magic number for file at '"<<filePath<<
            "' (Got: 0x"<< std::hex << std::setw(8) << std::setfill('0')<<magic_number<<
            ", Expected: 0x"<<expected<<"). The file is malformed or of the wrong format.";
        throw std::invalid_argument(error.str());
    }
}



template <typename intType>
intType FileUtil::readInt(std::ifstream& file)
{
    
    intType toReturn = 0;
    file.read((char*)&toReturn, sizeof(intType));

    if(std::endian::native == std::endian::little)
    {
        // swap the bits around if we're on x86 (I mean, Max has a mac I think so this could run on arm, right?)
        return std::byteswap<intType>(toReturn);
    }

    return toReturn;
}


template <typename intType>
void FileUtil::writeInt(std::ofstream& file, intType toWrite)
{

    if(std::endian::native == std::endian::little)
    {
        // swap the bits around if we're on x86 (I mean, Max has a mac I think so this could run on arm, right?)
        toWrite = std::byteswap<intType>(toWrite);
    }
    
    uint32_t toReturn = 0;
    file.write( reinterpret_cast<char*>(&toWrite), sizeof(intType));
}

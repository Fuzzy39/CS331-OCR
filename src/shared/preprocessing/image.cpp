#include "preprocessing/image.h"
#include <iostream>

using namespace ocr;

// implementation of the Image class

ocr::Image::Image(size_t width, size_t height, Format format)
{
    // do thingsgt7u8i6yyfdlugfl98
}

ocr::Image::Image(size_t width, size_t height, Format format, char* const data)
{

}

ocr::Image::Image(std::string filename, size_t width, size_t height)
{

}

ocr::Image::Format Image::getImageFormat()
{
    throw "NOT IMPLEMENTED";
}

size_t ocr::Image::getWidth()
{
    throw "NOT IMPLEMENTED";
}

size_t ocr::Image::getHeight()
{
    throw "NOT IMPLEMENTED";
}

void ocr::Image::writeToFile(std::string path)
{

}

std::unique_ptr<Vector<double>> ocr::Image::asFlatVector(Image::Format desiredFormat)
{
    throw "NOT IMPLEMENTED";
}

std::optional<Matrix<std::uint8_t>>& ocr::Image::getChannel(Image::Channel ch)
{
    throw "NOT IMPLEMENTED";
}

std::unique_ptr<Vector<double>> ocr::Image::getChannelAsVector(Image::Channel ch)
{
    throw "NOT IMPLEMENTED";
}
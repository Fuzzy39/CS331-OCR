#include "preprocessing/image.h"
#include <iostream>

using namespace ocr;

// implementation of the Image class
void func()
{
    std::cout<<"???";
}

Image::Image(size_t width, size_t height, Format format)
{
    // do thingsgt7u8i6yyfdlugfl98
}

Image::Image(size_t width, size_t height, Format format, const uint8_t& data)
{

}

Image::Image(std::string filename, size_t width, size_t height)
{

}

Image::Format Image::getImageFormat()
{
    throw "NOT IMPLEMENTED";
}

size_t Image::getWidth()
{
    throw "NOT IMPLEMENTED";
}

size_t Image::getHeight()
{
    throw "NOT IMPLEMENTED";
}

void Image::writeToFile(std::string path)
{

}

std::unique_ptr<Vector<double>> Image::asFlatVector(Image::Format desiredFormat)
{
    throw "NOT IMPLEMENTED";
}

std::optional<Matrix<std::uint8_t>>& Image::getChannel(Image::Channel ch)
{
    throw "NOT IMPLEMENTED";
}

std::unique_ptr<Vector<double>> Image::getChannelAsVector(Image::Channel ch)
{
    throw "NOT IMPLEMENTED";
}
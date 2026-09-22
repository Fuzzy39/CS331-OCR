#include "preprocessing/image.h"

using namespace ocr;

// implementation of the Image class

Image::Image(size_t width, size_t height, Format format)
{
    // do things
}

Image::Image(size_t width, size_t height, Format format, const uint8_t& data)
{

}

Image::Image(std::string filename, size_t width, size_t height)
{

}

Image::Format Image::getImageFormat()
{

}

size_t Image::getWidth()
{

}

size_t Image::getHeight()
{

}

void Image::writeToFile(std::string path)
{

}

std::unique_ptr<Vector<double>> Image::asFlatVector(Image::Format desiredFormat)
{

}

std::optional<Matrix<std::uint8_t>>& Image::getChannel(Image::Channel ch)
{

}

std::unique_ptr<Vector<double>> Image::getChannelAsVector(Image::Channel ch)
{

}
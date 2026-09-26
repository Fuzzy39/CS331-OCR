#include "preprocessing/image.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace ocr;

// implementation of the Image class

ocr::Image::Image(size_t width, size_t height, Format format, char* const data)
{

}

ocr::Image::Image(std::string filename, size_t width, size_t height)
{

}

ocr::Image::Format Image::getImageFormat()
{
    return format;
}

size_t ocr::Image::getWidth()
{
    return width;
}

size_t ocr::Image::getHeight()
{
    return height;
}

void ocr::Image::writeToFile(std::string path)
{
    const int COMP = 0; // jpg compression? Maybe?
    const int QUALITY = 0; // jpg quality. Dunno what the values mean.
                        // We could just do BMPs but if we're gonna have a ton of them maybe we could save some space with jpg?

    path +=".jpg";
    std::vector<Image::Channel> channels = getChannelsForFormat(format);
    throw "NOT IMPLEMENTED";

    // This function can't be written without being able to extract data from the matricies.

    //int stbi_write_jpg(path.c_str() int w, int h, int comp, const void *data, int quality);
}

std::unique_ptr<ocr::Vector<double>> ocr::Image::asFlatVector(Image::Format desiredFormat)
{
    // can't
    throw "NOT IMPLEMENTED";
}

std::optional<Matrix<std::uint8_t>>& ocr::Image::getChannel(Image::Channel ch)
{
    Matrix<std::uint8_t>* channel;
    try
    {
        channel = data.at(ch).get();
    }
    catch( std::out_of_range e)
    {
        auto toReturn = std::optional<Matrix<std::uint8_t>>();
        return toReturn; // for some reason I couldn't make this one line?
    }

    // Now, is dereferencing a pointer to a large object just to make a reference of it bad?
    // Probably. This might be dumb. Not sure. Just gonna move on for now.
    auto toReturn = std::optional<Matrix<std::uint8_t>>(*channel);
    return toReturn;

}

std::unique_ptr<Vector<double>> ocr::Image::getChannelAsVector(Image::Channel ch)
{
    // can't.
    throw "NOT IMPLEMENTED";
}

std::vector<Image::Channel> ocr::Image::getChannelsForFormat(Format f)
{
    // this feels like a silly way to do this.
    std::vector<Image::Channel> toReturn;
    switch(f)
    {
    case Format::Grayscale:
        toReturn.push_back(Channel::Greyscale);
        break;
    case Format::RGB:
        toReturn.push_back(Channel::R);
        toReturn.push_back(Channel::G);
        toReturn.push_back(Channel::B);
        break;
    case Format::RGBA:
        toReturn.push_back(Channel::R);
        toReturn.push_back(Channel::G);
        toReturn.push_back(Channel::B);
        toReturn.push_back(Channel::A);
        break;
    }

    return toReturn;
}

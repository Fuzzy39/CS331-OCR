#include "preprocessing/image.h"
#include <iostream>
#include <utility>
#include <sstream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace ocr;

// implementation of the Image class

ocr::Image::Image(size_t width, size_t height, Format format, const char* const data)
    : width(width), height(height), format(format), data()
{
   populateMap(data);
}

ocr::Image::Image(std::string filename, size_t width, size_t height)
    : width(width), height(height), format(Image::Format::Grayscale), data()
{
    int actualWidth = 0;
    int actualHeight = 0;
    int numChannels = 0;
    char* data = reinterpret_cast<char*>(stbi_load(filename.c_str(), &actualWidth, &actualHeight, &numChannels, 0));
    if(data == NULL)
    {
        throw std::invalid_argument(stbi_failure_reason());
    }

    // if the image isn't the size we expect, throw a tantrum. How dare they?
    if(actualWidth != width || actualHeight != height)
    {
        std::ostringstream error;
        error<<"Expected an image of size ("<<width<<", "<<height<< "). Got ("
            <<actualWidth<<", "<<actualHeight<<").";
        throw std::invalid_argument(error.str());
    }

    // now that we have the image data, we know what format we are.
    switch(numChannels)
    {
    case 1:
        format = Image::Format::Grayscale;
        break;
    case 3:
        format = Image::Format::RGB;
        break;
    case 4:
        format = Image::Format::RGBA;
        break;
    default:
        throw std::invalid_argument("Image had an unusual number of channels.");
    }
 throw std::invalid_argument(stbi_failure_reason());
    // now actually put away the data and store it properly.
    populateMap(data);
    stbi_image_free(data);
}

void ocr::Image::populateMap( const char* const data)
{

    std::vector<Image::Channel> channels = getChannelsForFormat(format);

    // create the map
    std::map<Channel, std::unique_ptr<Matrix<uint8_t>>>& map = this->data;
    // create a temporary vector to fill the matrix.
    std::vector<std::vector<std::vector<uint8_t>>> imageData;

    for(Image::Channel ch : channels)
    {
        // fill them with empty husks before we populate them
        map.emplace(Image::Channel::Greyscale, std::make_unique<ocr::Matrix<uint8_t>>(width, height));

    }

    // populate this giant vector (on the stack? seems dubious). 
    for(size_t i = 0; i<channels.size(); i++)
    {
        imageData.emplace_back();
        for(size_t x = 0; x<width; x++)
        {
            imageData[i].emplace_back();
            for(size_t y = 0; y<height; y++)
            {
              
                // pixels are stored by row, then column. Chanel data is contiguous.
                size_t index = channels.size()*(y*width + x)+i;
                uint8_t pixelData = static_cast<uint8_t>(data[index]);
                imageData.at(i).at(x).push_back(pixelData);
                
            }
        }
    }

  
    // pop the data in the matrices.
    int i = 0;
    for(Image::Channel ch : channels)
    {
        std::get<1>(*map.find(ch))->fill(imageData[i]);
        i++;
    }
    // We're now officially an image!
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
    const int COMP = getChannelsForFormat(format).size(); // COMPONENTS!
    const int QUALITY = 0; // jpg quality. Dunno what the values mean.
                        // We could just do BMPs but if we're gonna have a ton of them maybe we could save some space with jpg?

    path +=".jpg";
    std::vector<Image::Channel> channels = getChannelsForFormat(format);

    
    std::unique_ptr<std::vector<uint8_t>> rawFlatVector = asRawFlatVector(format);
    // This function can't be written without being able to extract data from the matricies.

    int returnValue = stbi_write_jpg(path.c_str(), width, height, COMP, rawFlatVector->data(), QUALITY);

    if(returnValue == 0)
    {
        // failure!
        throw std::invalid_argument("Couldn't write image file!");
    }
}

std::unique_ptr<ocr::Vector<double>> ocr::Image::asFlatVector(Image::Format desiredFormat)
{
    std::unique_ptr<std::vector<uint8_t>> rawFlatVector = asRawFlatVector(desiredFormat);

    // convert the normal byte vector to our own vector.
    auto doubleVec = std::make_unique<std::vector<double>>();

    for(uint8_t byte : *rawFlatVector)
    {
        doubleVec->push_back(byte/255.0);
    }

    auto toReturn = std::make_unique<ocr::Vector<double>>(doubleVec->size());
    toReturn->fill(*doubleVec);
    return toReturn;

}

std::unique_ptr<std::vector<uint8_t>> ocr::Image::asRawFlatVector(Format desiredFormat)
{
    // the implementation for this upsets me. There's definitely a better way to do this.

    std::vector<Image::Channel> channels = getChannelsForFormat(format);
    std::vector<ocr::Vector<uint8_t>> channelData;

    for(Image::Channel ch : channels)
    {
        auto matrix = getChannel(ch);
        channelData.push_back(ocr::Matrix<uint8_t>::flattenToVector(*matrix));
    }

    size_t vectorSize = getChannelsForFormat(format).size()*width*height;
    auto data = std::make_unique<std::vector<uint8_t>>();

    for(int i = 0; i<width*height; i++)
    {
        // yeah, this is going to get ugly.
        switch (desiredFormat)
        {
            case Image::Format::Grayscale:
            {
                // take the mean of other channels (except alpha)
                int lim = channelData.size();

                // this is a bit gross and hardcoded feeling...
                if(format == Image::Format::RGBA) lim = 3;
                uint16_t sum = 0;
                for(size_t j = 0; j<lim; j++)
                {
                    sum+=channelData[j][i];
                }

                data->push_back(static_cast<uint8_t>(sum/lim));
                break;
            }
            case Image::Format::RGB:
            {
                if(format == Image::Format::Grayscale)
                {
                    // for greyscale, just repeat the same value 3 times.
                    for(int j = 0; j<3; j++) data->push_back(channelData[0][i]);
                    break;
                }

                for(int j = 0; j<3; j++) data->push_back(channelData[j][i]);
                break;
            }
            case Image::Format::RGBA:
            {
                // this is disgusting. I'm sure there's a better way but I'm tired and want to be done soon.
                switch(format)
                {
                    case Image::Format::Grayscale:
                    {
                        for(int j = 0; j<3; j++) data->push_back(channelData[0][i]);
                        data->push_back(0xFF); // full alpha
                        break;
                    }
                    case Image::Format::RGB:
                    {
                        for(int j = 0; j<3; j++) data->push_back(channelData[j][i]);
                        data->push_back(0xFF);
                        break;
                    }
                    case Image::Format::RGBA:
                    {
                        for(int j = 0; j<4; j++) data->push_back(channelData[j][i]);
                        break;

                    }
                }
            break;
            }
        }
    }

    return data;
}


std::optional<Matrix<std::uint8_t>> ocr::Image::getChannel(Image::Channel ch)
{

    auto channelPair = data.find(ch);
    if(channelPair == std::end(data)) 
    {
        return {};
    }
    Matrix<std::uint8_t>* channel = std::get<1>(*channelPair).get();
    return std::optional(*channel);

}

std::unique_ptr<ocr::Vector<double>> ocr::Image::getChannelAsVector(Image::Channel ch)
{
    auto matrix = getChannel(ch);
    if(!matrix.has_value())
    {
        return std::unique_ptr<Vector<double>>(nullptr);
    }

    // convert from uint8_t to double
    auto rawData = std::make_unique<ocr::Vector<uint8_t>>(Matrix<uint8_t>::flattenToVector(*matrix));
    std::vector<double> doubleVec;
    for(int i = 0; i<rawData->getSize(); i++)
    {
        doubleVec.push_back((*rawData)[i]/255.0);
    }

    auto toReturn = std::make_unique<ocr::Vector<double>>(rawData->getSize());
    toReturn->fill(doubleVec);
    return toReturn;

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

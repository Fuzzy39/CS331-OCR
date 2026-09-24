#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <optional>
#include <memory>
#include "data_structures/matrix.h"

namespace ocr
{

    class Image
    {
    public:

        enum class Format
        {
            // If this were to be more general we'd really need two enums for this - one to describe the format of data internally and one for how we're outputing it as a vector.
            // Although we would probably want to consider more robust ways to implement things if we felt the need to go that far.
            Grayscale, // 1 byte per pixel
            RGB, // 3 bytes per pixel
            RGBA // 4 bytes per pixel
        };

        enum class Channel
        {
            Greyscale,
            R,
            G,
            B,
            A,
        };

    private:

        size_t width;
        size_t height;
        Format format;
        std::map<Channel, Matrix<uint8_t>> data;


    public:
        /// @brief Creates an empty image of all black pixels.
        Image(size_t width, size_t height, Format format);

        /// @brief Create an image with the specified format from the given data. It is assumed all channels are 8 bits.
        Image(size_t width, size_t height, Format format, char* const data);

        /// @brief Reads image from a file, forcing it to fit a particular size.
        ///        If the image is too small, the data will be put in the top left corner and remaining pixels will be black.
        ///        If the image is too large, individual will be sampled at intervals to produce a smaller image. The image is not blured.
        Image(std::string filename, size_t width, size_t height);


        Format getImageFormat();
        size_t getWidth();
        size_t getHeight();


        /// @brief Writes an image to the given path, in the format given by the file extension provided. Overrides any prexisting file.
        /// @param path 
        void writeToFile(std::string path);


        /// @brief converts the data of the image to a flat vector.
        /// @param desiredFormat describes the way the image data should be converted:
        ///        Grey8 - all channels will be averaged and there will be one entry per pixel in the output
        ///        RGB8  - If the image is in greyscale, the same value will be repeated 3 times for each pixel. 
        ///             If not, the alpha channel is discarded and each pixel is represented with a 3 values: R, G and B.
        ///        RGBA  - each pixel is represented with 4 values: Red, Green Blue and Alpha. Color channels are treated as RGB8 for greyscale images. If the image does not
        //              Have an alpha channel, it will always be 1 in the output.
        /// @return Returns a vector of size width*height*size of desired format. pixel data is always grouped sequentially, 
        ///         and pixel data is outputed left to right, then top to bottom.
        std::unique_ptr<Vector<double>> asFlatVector(Format desiredFormat);

        
        /// @brief Returns the raw data of the given channel, if present.
        std::optional<Matrix<std::uint8_t>>& getChannel(Channel ch);

        /// @brief Returns a vector of the data of a given channel.     
        std::unique_ptr<Vector<double>> getChannelAsVector(Channel ch);


    };
}
#endif
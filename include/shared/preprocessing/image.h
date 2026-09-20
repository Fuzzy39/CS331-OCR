#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <cstdint>
#include "data_structures/matrix.h"

enum class PixelFormat {
    Gray8, // 1 byte per pixel
    RGB8, // 3 bytes per pixel
    RGBA8 // 4 bytes per pixel
};

class Image : public AbstractMatrix<std::uint8_t> {
public:
    Image(int width, int height, PixelFormat format);
    
    PixelFormat getPixelFormat();
    std::string getPath();

    std::vector<std::uint8_t> getPixelData();
    void setPixelData(std::vector<std::uint8_t> data);
    void writeToFile(std::string path);

private:
    std::string path;
    PixelFormat format;
    std::vector<std::uint8_t> pixelData;
};

#endif
#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <format>

#include "dataset.h"
#include "dataset.ipp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        std::cerr << "Usage: " << argv[0]
        << " <dataset-folder> <output-folder> [max-images]\n";
        return 1;
    }

    std::string folderPath = argv[1];
    std::string outputPath = argv[2];
    int maxImages = -1;

    try { // Max-Image Handling
            maxImages = std::stoi(argv[3]);
            if (maxImages < -1) {
                maxImages = -1;
            }
    }
    catch (...) {
        std::cerr << "Max-images must be an integer";
        return 1;
    }


    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) { // Verify dataset folder exists.
        std::cerr << "Dataset folder does not exist: " << folderPath << '\n';
        return 1;
    }

    try { // Create output path
        fs::create_directories(outputPath);
    }
    catch (fs::filesystem_error& e)
    {
        std::cerr << "Error creating output folder: "
                  << e.what() << '\n';
        return 1;
    }


    try { // Dataset Handling
        std::string imagePath = folderPath + "/emnist-digits-test-images-idx3-ubyte";
        std::string labelPath = folderPath + "/emnist-digits-test-labels-idx1-ubyte";
        
        ocr::Dataset<int> data(imagePath, labelPath);
        int index = 0;

        // Iterate through the dataset's images
        for (auto& img : data.getAllImages()) {
            if (maxImages >= 0 && index >= maxImages) { break; } // Limit

            int imageId = data.getLabel(index);

            std::string filename = std::to_string(imageId) + "-" + std::to_string(index) + ".png";

            img.writeToFile(outputPath + "/" + filename);

            index += 1;
        }

        std::cout << "Extracted "<< index << " images to " << outputPath << '.\n';
    }
    catch (std::exception& e) {
        std::cerr << "Error extracting dataset: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

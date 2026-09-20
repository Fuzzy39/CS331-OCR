#ifndef DATASET_H
#define DATASET_H

#include "data_structures/vector.h"
#include "data_structures/matrix.h"
#include "preprocessing/image.h"
#include <string>

class Dataset {
public:
    Dataset(std::string imagePath, std::string labelPath);

    // images
    Image getImage(size_t index);
    std::vector<Image> getAllImages();

    // labels
    Vector<double> getLabel(size_t index);
    Vector<double> getAllLabels();


private:
    std::string imagePath;
    std::string labelPath;
    std::vector<Image> images;
    Vector<double> labels;
};

#endif
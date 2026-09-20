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
    Vector getAllImages();

    // labels
    Vector getLabel(size_t index);
    Vector getAllLabels();


private:
    std::string imagePath;
    std::string labelPath;
    Vector images;
    Vector labels;
};

#endif
#include "preprocessing/dataset.h"
#include "preprocessing/image.h"
#include <stdexcept>

namespace ocr {
    template <typename T>
    Batch<T>::Batch(size_t batchSize, std::vector<Image>::iterator images, iterator labels):batchSize(batchSize), images(images), labels(labels) {

    }

    template <typename T>
    size_t Batch<T>::getSize() {
        return batchSize;
    }

    template <typename T>
    ocr::Image &Batch<T>::getImage(size_t index) {
        if (index >= batchSize) {
            throw std::out_of_range("Out of range batch index");
        }
        return images[index];
    }

    template <typename T>
    T Batch<T>::getLabel(size_t index) {
        if (index >= batchSize) {
            throw std::out_of_range("Out of range batch index");
        }
        return labels[index];
    }
}

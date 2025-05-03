#include "Image.h"


Image::Image() {}

Image::Image(std::string path) : File(path) {}

Matrix<bool>* Image :: getMonochromeImage()
{
    return &monochrome_image_;
}
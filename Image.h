#pragma once
#include "File.h"
#include "Matrix.h"
//#include <vector>
class Image: 
    public File
{
private:
    Matrix<bool> monochrome_image_;
public:
    Image();
    Image(std::string path);
    virtual void setMonochromeImage()=0;
    virtual void setHeight()=0;
    virtual void setWidth()=0;
    Matrix<bool>* getMonochromeImage();
};


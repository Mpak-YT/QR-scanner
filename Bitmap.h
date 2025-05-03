#pragma once
#include "Image.h"
#include <queue>
#include "BitsChunk.h"

class BitmapMonochrome :
    public Image
{
private:
    std::queue<BitsChunk> data_lines;
public:

    BitmapMonochrome();
    BitmapMonochrome(std::string path);


    void setMonochromeImage () override;
    void setHeight() override;
    void setWidth() override;
};


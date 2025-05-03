#include "Bitmap.h"
BitmapMonochrome::BitmapMonochrome() 
{
	setHeight();
	setWidth();
	
	for (int i = 0; i < getMonochromeImage()->get_height(); i++)
	{
		BitsChunk line{getFile(), (i * nearest_multiple(getMonochromeImage()->get_width(), 32)/8 + 0x3e), getMonochromeImage()->get_width()};
		data_lines.push(std::move(line));
	}
	setMonochromeImage();
}

BitmapMonochrome::BitmapMonochrome(std::string path) : Image(path) 
{
	setHeight();
	setWidth();
	
	for (int i = 0; i < getMonochromeImage()->get_height(); i++)
	{
		BitsChunk line{getFile(), (i * nearest_multiple(getMonochromeImage()->get_width(), 32)/8 + 0x3e), getMonochromeImage()->get_width()};
		data_lines.push(std::move(line));
	}
	setMonochromeImage();
}

void BitmapMonochrome::setMonochromeImage()
{
	char byte;
	int k = 0;
	for (int i=getMonochromeImage()->get_height()-1; i>=0; i--, data_lines.pop())
		for (int j = 0; 8*j+k < getMonochromeImage()->get_width(); j++, k = 0)
			for (k = 0; k < 8 && 8 * j + k < getMonochromeImage()->get_width(); k++)
			{
				byte = data_lines.front().get_data()[j];
				getMonochromeImage()->at(i, 8*j+k) = (byte >> 7-k) & 0b1;
				/*
				if ((byte >> 7 - k) & 1)
					printf(" ");
				else
					printf("*", 254);*/
			}
	/*
	printf("\n\n\n");
	for (int i=0; i< getMonochromeImage()->get_height(); i++, printf("\n"))
	{
		for (int j = 0; j < getMonochromeImage()->get_width(); j++)
		{
			if (getMonochromeImage()->at(i, j))
				printf(" ");
			else
				printf("*", 254);
		}
	}*/
}
void BitmapMonochrome::setHeight()
{
	BitsChunk height{ getFile(), 0x16, 32 };
	getMonochromeImage()->resize_h(height.chunk_to_int());
}

void BitmapMonochrome::setWidth()
{
	BitsChunk width{ getFile(), 0x12, 32 };
	getMonochromeImage()->resize_w(width.chunk_to_int());
}
#include "QrCode.h"
#include <conio.h>

void convertBoolMatrixToByteArray(Matrix<bool>& boolMatrix, unsigned char* data) {
    int height = boolMatrix.get_height(); int width = boolMatrix.get_width(); for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            data[y * width + x] = boolMatrix.at(y, x) ? 0 : 255; // 0 дл€ черного, 255 дл€ белого 
        }
    }
}

QR::QR(Matrix<bool>* image)
{
    unsigned char* data = new unsigned char[image->get_width() * image->get_height()];
   // int x = image->get_height();
    setVersion(image);
    convertBoolMatrixToByteArray(*image, data);
    if (image->get_height() == image->get_width())
    {
        if (version <= 2)
        {
            unmask(image);
            reading(image);
            std::cout << "QRCode: ";
            decoding();
        }
        else
        {

            auto Image = ZXing::ImageView(data, image->get_width(), image->get_height(), ZXing::ImageFormat::Lum);
            auto options = ZXing::ReaderOptions().setFormats(ZXing::BarcodeFormat::QRCode); // ”казываем формат QR-кода
            auto barcodes = ZXing::ReadBarcodes(Image, options);
            try
            {
                if (barcodes.empty())
                {
                    throw(InvalidQRFind("No QR found!"));
                }
            }
            catch (InvalidQRFind& exception)
            {
                std::cout << exception << std::endl;
                return;
            }
            for (const auto& b : barcodes) {
                std::cout << ZXing::ToString(b.format()) << ": " << b.text() << "\n";
            }
        }
    }
    else
    {

        auto Image = ZXing::ImageView(data, image->get_width(), image->get_height(), ZXing::ImageFormat::Lum);
        auto options = ZXing::ReaderOptions().setFormats(ZXing::BarcodeFormat::LinearCodes);
        auto barcodes = ZXing::ReadBarcodes(Image, options);
        try
        {
            if (barcodes.empty())
            {
                throw(InvalidQRFind("No BarCode EAN13 found!"));
            }
        }
        catch (InvalidQRFind& exception)
        {
            std::cout << exception << std::endl;
            return;
        }
        for (const auto& b : barcodes) {
            std::cout << ZXing::ToString(b.format()) << ": " << b.text() << "\n";
        }
    }

}

short unsigned QR::getMuskNumber(Matrix<bool>* image)
{
    return (image->at(8, 2) + 2*(1^image->at(8, 3)) + 4*(image->at(8, 4)));
}


/*

unmask_000            (i+j)%2 == 0
unmask_001            i%2 == 0
unmask_010            j%3 == 0
unmask_011            (i+j)%3 == 0

unmask_100            (i/2 + j/3)%2 == 0
unmask_101            i*j%2 + i*j%3 == 0
unmask_110            (i*j%2 + i*j%3)%2 == 0
unmask_111            ((i+j)%2 + (i+j)%3)%2 == 0





*/

void QR::unmask(Matrix<bool>* image)
{
    int m = getMuskNumber(image);
    for(int i=0; i < image->get_height(); i++)
        for(int j=0; j < image->get_width(); j++)
            if(
                (m == 0 && (i+j)%2==0)                  ||
                (m == 1 && i%2==0)                      ||
                (m == 2 && j%3 == 0)                    ||
                (m == 3 && (i+j)%3 == 0)                ||
                (m == 4 && (i/2 + j/3)%2 == 0)          ||
                (m == 5 && i*j%2 + i*j%3 == 0)          ||
                (m == 6 && (i*j%2 + i*j%3)%2 == 0)      ||
                (m == 7 && ((i+j)%2 + (i*j)%3)%2 == 0)
              )
                image->at(i, j) ^= 1;
/*
    
    printf("\n\n\n");            
    for (int i=0; i< image->get_height(); i++, printf("\n"))
	{
		for (int j = 0; j < image->get_width(); j++)
		{
			if (image->at(i, j))
				printf(" ");
			else
				printf("*", 254);
		}
	}
    */
}

bool QR::isMark(Matrix<bool>* image, int i, int j)
{    
    return (i <= 8 && ((j > image->get_width() - 1 - 8) || (j <= 8) || //* i=0--8, j=0--8     //* i=0--8, j=(width-1-8)--(width-1)
           (i == 6) ||     //* i=6, j=9--12
           (i > image->get_height()) - 1 - 8 && j <= 8) ||   //* i=(height-1-8)--(height-1), j=0--8
           (version>=2 && version<=6 && 8+4*version <= i && 12+4*version >= i && 8 + 4 * version <= j && 12 + 4 * version >= j) ||//*version= 2-6
           (0)); 
            
}

void QR::readPixel(Matrix<bool>* image, int i, int j)
{
    if (!isMark(image, i, j))
        data.push(image->at(i, j));
}

void QR::reading(Matrix<bool>* image){
    bool up = 0;
    int i = image->get_height() - 1, j = image->get_width();
    while(1)
    {
        if (i == image->get_height() - 1 || i == 0)
        {
            up ^= 1;
            if (j == 7) j--; //! i=9--12, j=6
            j--;
            readPixel(image, i, j);
            j--;
            readPixel(image, i, j);
        }
       // (((j<7) ? j-1 : j) % 2 == 0) ? i :
            (up ? --i : ++i);
        j++;
        readPixel(image, i, j);
        //((j < 7) ? j - 1 : j) % 2 == 1 ? j++ : j--;
         j--;
        readPixel(image, i, j);
        if (j == 0 && i == 21 - 1)
            break;
    }
}

void QR::decoding()
{
    int header=0, blocks_number=0;
    char block = '\0';


    for (int i = 0; i < 4; i++)
    {
        header += (1^data.front()) * exp<int>(2, 3-i);
        data.pop();
    }
    for (int i = 0; i < 8; i++)
    {
        blocks_number += (1^data.front()) * exp<int>(2, 7-i);
        data.pop();
    }
    for (int i = 0; i < blocks_number; i++, printf("%c", block), block = '\0')
    {
        for (int j = 0; j < 8; j++)
        {
            block += (1^data.front()) * exp<int>(2, 7-j);
            data.pop();
        }
    }
}

void QR::setVersion(Matrix<bool>* image)
{
    for (version = 1; 17 + version * 4 < image->get_height(); version++);
}

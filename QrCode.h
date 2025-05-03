#pragma once
#include "Matrix.h"
#include "Math.h"
#include <queue>
#include "InvalidQRFind.h"



// Класс LuminanceSource для работы с Matrix<bool>
#include "ReadBarcode.h"
#include <iostream>





class QR
{
private:
	int mask;
	int version;
	std::queue<bool> data;
	//*i=8, j=2-4 - mask
public:
    QR(Matrix<bool>* image);
	short unsigned getMuskNumber(Matrix<bool>* image);
	void unmask(Matrix<bool>* image);
	void reading(Matrix<bool>* image);
	bool isMark(Matrix<bool>* image, int i, int j);
	void readPixel(Matrix<bool>* image, int i, int j);
	void decoding();
	void setVersion(Matrix<bool>* image);
	//unsigned short operator()(unsigned short nBit);
};
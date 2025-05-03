#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <regex>
#include "InvalidFileOpen.h"
#include "InvalidFileFormat.h"

#define SUPPORTED true
#define NOT_SUPPORTED !SUPPORTED

class File
{
private:
	std::string filename_; //path to file
	std::ifstream file_;	 //pointer to file
public:
	File();
	File(std::string path);
	~File();
	void openFile();
	void setFilename();
	
	std::string& getFilename();
	std::ifstream& getFile();

	bool isSupported();
};

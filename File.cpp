#include "File.h"
/**
** PNG 89 50 4e 47 (hPNG)
** BMP 42 4d (BM)
** JPG ff d8 ff

** JPG  jpg, jpeg, jpe, jfif
** BMP  bmp, dib
** PNG  png
*/

File::File()
{
	file_.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	while (1)
	{
		setFilename();
		try
		{
			openFile();
		}
		catch (InvalidFileOpen& exception)
		{
			std::cout << exception << std::endl;
			if(file_.is_open())
				file_.close();
			file_.clear();
			continue;
		}
		catch (InvalidFileFormat& exception)
		{
			std::cout << exception << std::endl;
			file_.close();
			file_.clear();
			continue;
		}
		break;
	}
}

File::File(std::string path) : filename_(path)
{
	file_.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		openFile();
	}
	catch (InvalidFileOpen& exception)
	{
		std::cout << exception << std::endl;
		if (file_.is_open())
			file_.close();
		file_.clear();
	}
	catch (InvalidFileFormat& exception)
	{
		std::cout << exception << std::endl;
		file_.close();
		file_.clear();
	}
}

File::~File()
{
	file_.close();
	//delete& filename_;
}

void File::openFile()
{
	try
	{
		file_.clear();
		file_.open(filename_.c_str(), std::ios::binary);
	}
	catch(std::ios_base::failure & e)
	{
		throw (InvalidFileOpen("No file found!"));
	}
		
	if (!isSupported())
		throw (InvalidFileFormat("This file format does not supported!"));
}

void File::setFilename()
{
	getline(std::cin, filename_);
}

std::string& File::getFilename()
{
	return filename_;
}

std::ifstream& File::getFile()
{
	return file_;
}

bool File::isSupported()
{
	std::regex pattern(".*\\.(bmp|dib)$", std::regex_constants::icase);
	if (std::regex_match(filename_, pattern))
		return SUPPORTED;
	else
		return NOT_SUPPORTED;
}
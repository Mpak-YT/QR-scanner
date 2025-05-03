#include "InvalidFileFormat.h"
InvalidFileFormat::InvalidFileFormat(const std::string& message) : Exception(message) {}

/*
std::string InvalidFileFormat::getMessage() const
{
	return Exception::getMessage();
}
/*
std::ostream& operator<<(std::ostream& os, InvalidFileFormat& exception)
{
	os << exception.getMessage();
	return os;
}
*/
#include "InvalidFileOpen.h"
InvalidFileOpen::InvalidFileOpen(const std::string& message) : Exception(message) {}

/*
std::string InvalidFileOpen::getMessage() const
{
	return Exception::getMessage();
}
/*
std::ostream& operator<<(std::ostream& os, InvalidFileOpen& exception)
{
	os << exception.getMessage();
	return os;
}
*/
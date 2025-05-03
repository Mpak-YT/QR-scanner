#include "Exception.h"

Exception::Exception(const std::string& message) : message_(message) {}

std::string Exception::getMessage() const
{
	return message_;
}

std::ostream& operator<<(std::ostream& os, Exception& exception)
{
	os << exception.message_;
	return os;
}

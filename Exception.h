#pragma once
#include <iostream>
#include <string>

class Exception
{
private:
	std::string message_;
public:
    Exception(const std::string& message);
    std::string getMessage() const;
    friend std::ostream& operator<< (std::ostream& os, Exception& exception);
};


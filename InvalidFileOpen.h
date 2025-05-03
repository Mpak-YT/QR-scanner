#pragma once
#include "Exception.h"
class InvalidFileOpen :
    public Exception
{
public:
    InvalidFileOpen(const std::string& message);
};


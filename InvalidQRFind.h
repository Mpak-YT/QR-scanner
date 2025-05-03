#pragma once
#include "Exception.h"
class InvalidQRFind :
    public Exception
{
public:
    InvalidQRFind(const std::string& message);
};


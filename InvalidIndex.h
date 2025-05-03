#pragma once
#include "Exception.h"
class InvalidIndex :
    public Exception
{
public:
    InvalidIndex(const std::string& message);
};


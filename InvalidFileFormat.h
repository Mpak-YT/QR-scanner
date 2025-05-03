#pragma once
#include "Exception.h"
class InvalidFileFormat :
    public Exception
{
public:
    InvalidFileFormat(const std::string& message);
 };
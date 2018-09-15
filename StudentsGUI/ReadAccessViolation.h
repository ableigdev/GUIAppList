#pragma once

#include <stdexcept>

class ReadAccessViolation : public std::runtime_error
{
public:
    ReadAccessViolation()
        : std::runtime_error("Read access violation")
    {

    }
};
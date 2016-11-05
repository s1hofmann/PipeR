#pragma once

#include "BaseError.h"

namespace pl {


class CommandLineError : public BaseError
{
public:
    CommandLineError(const std::string &msg,
                     const std::string &where = std::string(),
                     const int32_t line = -1);
};


}

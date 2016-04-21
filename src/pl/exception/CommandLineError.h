#pragma once

#include "BaseError.h"

namespace pl {


class CommandLineError : public BaseError
{
public:
    CommandLineError(const std::string &msg,
                     const std::string &where = std::string(),
                     const int line = -1);
};


}

#pragma once

#include "BaseError.h"

namespace pl {


class OCVError : public BaseError {
public:
    OCVError(const std::string &msg,
             const std::string &where = std::string(),
             const int line = -1);
};


}

#pragma once

#include "BaseError.h"

namespace pl {


class FeatureExError : public BaseError {
public:
    FeatureExError(const std::string &msg,
                   const std::string &where = std::string(),
                   const int32_t line = -1);
};


}

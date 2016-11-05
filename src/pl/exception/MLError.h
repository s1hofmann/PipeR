#pragma once

#include "BaseError.h"

namespace pl {


class MLError : public BaseError {
public:
    MLError(const std::string &msg,
            const std::string &where = std::string(),
            const int32_t line = -1);
};


}

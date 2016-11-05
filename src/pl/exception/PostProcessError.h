#pragma once

#include "BaseError.h"

namespace pl {


class PostProcessError : public BaseError {
public:
    PostProcessError(const std::string &msg,
                     const std::string &where = std::string(),
                     const int32_t line = -1);
};


}

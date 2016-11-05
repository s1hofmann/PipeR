#pragma once

#include "BaseError.h"

namespace pl {


class EncodingError : public BaseError {
public:
    EncodingError(const std::string &msg,
                  const std::string &where = std::string(),
                  const int32_t line = -1);
};


}

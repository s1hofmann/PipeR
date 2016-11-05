#pragma once

#include "BaseError.h"

namespace pl {


class ClusterError : public BaseError {
public:
    ClusterError(const std::string &msg,
                 const std::string &where = std::string(),
                 const int32_t line = -1);
};


}

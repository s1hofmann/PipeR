#pragma once

#include <sstream>
#include <string>
#include "BaseError.h"

namespace pl {


class DimensionalityReductionError : public Error {
public:
    DimensionalityReductionError(const std::string &msg,
                                 const std::string &where = std::string(),
                                 const int line = -1);

private:
    virtual std::string getMsg(const std::string &msg,
                               const std::string &where = std::string(),
                               const int line = -1) const override;
};


}

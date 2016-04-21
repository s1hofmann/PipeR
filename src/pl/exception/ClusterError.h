#pragma once

#include <sstream>
#include <string>
#include "BaseError.h"

namespace pl {


class ClusterError : public Error {
public:
    ClusterError(const std::string &msg,
                 const std::string &where = std::string(),
                 const int line = -1);

private:
    virtual std::string getMsg(const std::string &msg,
                               const std::string &where = std::string(),
                               const int line = -1) const override;
};


}

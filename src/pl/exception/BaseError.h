#pragma once

#include <sstream>
#include <string>

namespace pl {


class BaseError : public std::runtime_error {
public:
    BaseError(const std::__1::string &errorType, const std::string &msg,
          const std::string &where = std::string(),
          const int32_t line = -1);

private:
    virtual std::string getMsg(const std::string &errorType,
                               const std::string &msg,
                               const std::string &where = std::string(),
                               const int32_t line = -1) const;
};


}

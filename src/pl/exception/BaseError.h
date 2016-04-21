#pragma once

#include <sstream>
#include <string>

namespace pl {


class Error : public std::runtime_error {
public:
    Error(const std::string &msg,
          const std::string &where = std::string(),
          const int line = -1);

private:
    virtual std::string getMsg(const std::string &msg,
                               const std::string &where = std::string(),
                               const int line = -1) const;
};


}

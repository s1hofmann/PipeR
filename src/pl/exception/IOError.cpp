#include "IOError.h"

namespace pl {

IOError::IOError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError(msg, where, line)
{
}

}

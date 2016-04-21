#include "BaseError.h"

namespace pl {

BaseError::BaseError(const std::string &msg, const std::string &where, const int line)
    :
        std::runtime_error("")
{
    std::string errorText = getMsg(msg, where, line);
    static_cast<std::runtime_error&>(*this) = std::runtime_error(errorText);
}

std::string BaseError::getMsg(const std::string &msg,
                              const std::string &where,
                              const int line) const
{
    std::stringstream s;
    if(!where.empty()) {
        s << "(Error in " << where << ", line " << line << ") ";
    }
    s << msg << std::endl;

    return s.str();
}

}

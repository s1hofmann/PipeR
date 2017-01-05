#include "BaseError.h"

namespace pl {

BaseError::BaseError(const std::string &errorType, const std::string &msg, const std::string &where, const int32_t line)
    :
        std::runtime_error("")
{
    std::string errorText = getMsg(errorType, msg, where, line);
    static_cast<std::runtime_error&>(*this) = std::runtime_error(errorText);
}

std::string BaseError::getMsg(const std::string &errorType,
                              const std::string &msg,
                              const std::string &where,
                              const int32_t line) const
{
    std::stringstream s;
    s << "(";
    if(!errorType.empty()) {
        s << errorType;
    } else {
        s << "Error";
    }
    if(!where.empty()) {
        s << "in function" << where;
    }
    if(line >= 0) {
        s << ", line " << line;
    }
    s << ") " << msg << std::endl;

    return s.str();
}

}

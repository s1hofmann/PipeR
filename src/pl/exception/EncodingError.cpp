#include "EncodingError.h"

namespace pl {

EncodingError::EncodingError(const std::string &msg, const std::string &where, const int line)
    :
        Error(msg, where, line)
{
}

std::string EncodingError::getMsg(const std::string &msg,
                                  const std::string &where,
                                  const int line) const
{
    std::stringstream s;
    if(!where.empty()) {
        s << "(Encoding error in " << where << ", line " << line << ") ";
    }
    s << msg << std::endl;

    return s.str();
}

}

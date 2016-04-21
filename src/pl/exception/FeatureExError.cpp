#include "FeatureExError.h"

namespace pl {

FeatureExError::FeatureExError(const std::string &msg, const std::string &where, const int line)
    :
        Error(msg, where, line)
{
}

std::string FeatureExError::getMsg(const std::string &msg,
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

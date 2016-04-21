#include "ClusterError.h"

namespace pl {

ClusterError::ClusterError(const std::string &msg, const std::string &where, const int line)
    :
        Error(msg, where, line)
{
}

std::string ClusterError::getMsg(const std::string &msg,
                                 const std::string &where,
                                 const int line) const
{
    std::stringstream s;
    if(!where.empty()) {
        s << "(Clustering error in " << where << ", line " << line << ") ";
    }
    s << msg << std::endl;

    return s.str();
}

}

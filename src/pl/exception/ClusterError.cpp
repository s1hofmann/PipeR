#include "ClusterError.h"

namespace pl {

ClusterError::ClusterError(const std::string &msg, const std::string &where, const int line)
    :
        BaseError(msg, where, line)
{
}

}

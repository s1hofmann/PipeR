#include "ClusterError.h"

namespace pl {

ClusterError::ClusterError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError("ClusterError", msg, where, line)
{
}

}

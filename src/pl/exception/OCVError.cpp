#include "OCVError.h"

namespace pl {

OCVError::OCVError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError("OpenCVError", msg, where, line)
{
}

}

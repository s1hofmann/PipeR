#include "DimensionalityReductionError.h"

namespace pl {

DimensionalityReductionError::DimensionalityReductionError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError("DimensionalityReductionError", msg, where, line)
{
}

}

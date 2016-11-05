#include "FeatureExError.h"

namespace pl {

FeatureExError::FeatureExError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError(msg, where, line)
{
}

}

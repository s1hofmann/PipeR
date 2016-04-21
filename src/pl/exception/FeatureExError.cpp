#include "FeatureExError.h"

namespace pl {

FeatureExError::FeatureExError(const std::string &msg, const std::string &where, const int line)
    :
        BaseError(msg, where, line)
{
}

}

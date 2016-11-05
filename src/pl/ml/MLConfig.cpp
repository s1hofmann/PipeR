#include "MLConfig.h"

namespace pl {

MLConfig::~MLConfig()
{

}

MLConfig::MLConfig(const std::string &identifier,
                   const int32_t folds)
    :
        ConfigContainer(identifier),
        mFolds(folds)
{

}

int32_t MLConfig::folds() const
{
    return mFolds;
}

void MLConfig::setFolds(int32_t folds)
{
    mFolds = folds;
}

}

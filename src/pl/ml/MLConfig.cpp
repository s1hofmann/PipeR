#include "MLConfig.h"

namespace pl {

MLConfig::~MLConfig()
{

}

MLConfig::MLConfig(const std::string &identifier,
                   const int folds)
    :
        ConfigContainer(identifier),
        mFolds(folds)
{

}

int MLConfig::folds() const
{
    return mFolds;
}

void MLConfig::setFolds(int folds)
{
    mFolds = folds;
}

}

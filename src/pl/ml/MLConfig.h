#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pl {


class MLConfig : public ConfigContainer
{
public:
    virtual ~MLConfig();

    int folds() const;
    void setFolds(int folds);

protected:
    MLConfig(const std::string &identifier,
             const int folds = 5);

    int mFolds;
};


}

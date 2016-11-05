#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pl {


class MLConfig : public ConfigContainer
{
public:
    virtual ~MLConfig();

    int32_t folds() const;
    void setFolds(int32_t folds);

protected:
    MLConfig(const std::string &identifier,
             const int32_t folds = 5);

    int32_t mFolds;
};


}

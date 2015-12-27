#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pl {


class BinarizationConfig : public ConfigContainer
{
public:
    BinarizationConfig(std::string &methodName);
    virtual ~BinarizationConfig();
};


}

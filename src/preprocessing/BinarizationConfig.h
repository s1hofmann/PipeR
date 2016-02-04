#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pl {


class BinarizationConfig : public ConfigContainer
{
public:
    BinarizationConfig(const std::string &identifier,
                       const std::string &methodName = "su");
    virtual ~BinarizationConfig();
};


}

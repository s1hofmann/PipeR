//
// Created by Simon Hofmann on 19.11.15.
//

#include <sstream>
#include "FeatureConfig.h"

namespace pl {


FeatureConfig::FeatureConfig(const std::string &identifier,
                             const bool augment)
    :
        ConfigContainer(identifier,
                        "Parameter description",
                        "Help text"),
        mAugment(augment)
{
}


FeatureConfig::~FeatureConfig()
{

}


std::string FeatureConfig::toString() const
{
    std::stringstream configString;

    configString << "Augment: ";
    if(mAugment == true) {
        configString << "true" << std::endl;
    } else {
        configString << "false" << std::endl;
    }

    return configString.str();
}

bool FeatureConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mAugment = params.get(varName(mAugment), true).asBool();

        return true;
    }
}

bool FeatureConfig::augment() const
{
    return mAugment;
}

bool FeatureConfig::setAugment(bool augment)
{
    mAugment = augment;
    return setConfigParameter<bool>(varName(mAugment), augment);
}


}

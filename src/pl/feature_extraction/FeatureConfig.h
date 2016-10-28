//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pl {


/**
 * @brief The SiftConfigContainer class
 */
class FeatureConfig : public ConfigContainer {
public:
    FeatureConfig(const std::string &identifier,
                  const bool augment);

    /**
     * @brief ~SiftConfigContainer
     */
    virtual ~FeatureConfig();

    virtual bool augment() const;
    virtual bool setAugment(bool augment);

    // ConfigContainer interface
    std::string toString() const;
    bool fromJSON(std::string &file);

protected:
    /**
     * @brief mAugment
     */
    bool mAugment;
};


}

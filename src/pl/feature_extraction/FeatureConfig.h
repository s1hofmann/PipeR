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
                  const bool augment = true);

    /**
     * @brief ~SiftConfigContainer
     */
    virtual ~FeatureConfig();

    bool augment() const;
    void setAugment(bool augment);

    // ConfigContainer interface
    std::string toString() const;
    bool fromJSON(std::string &file);

private:
    /**
     * @brief mAugment
     */
    bool mAugment;
};


}

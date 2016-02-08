//
// Created by Simon Hofmann on 11.12.15.
//


#pragma once

#include <string>
#include <fstream>
#include <opencv2/core/core.hpp>
#include "../core/utils/json/json.h"
#include "../pipeline/globals.h"

namespace pl {

class MaskGenerator {
public:
    virtual ~MaskGenerator();

    virtual cv::Mat create(const cv::Mat &input) = 0;

    virtual std::string toString() = 0;

    virtual bool fromJSON(const std::string &file) = 0;

    virtual std::string identifier() = 0;

protected:
    MaskGenerator(const std::string &identifier = "Mask generator");

    Json::Value readJSON(const std::string &file);

    std::string mIdentifier;
};


}

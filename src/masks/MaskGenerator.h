//
// Created by Simon Hofmann on 11.12.15.
//


#pragma once

#include <string>
#include <opencv2/core/core.hpp>

namespace pipe {

class MaskGenerator {
public:
    MaskGenerator(const std::string &name = "Mask");

    virtual ~MaskGenerator();

    virtual cv::Mat create(const cv::Mat &input) = 0;

    virtual std::string toString() = 0;

protected:
    std::string mName;
};


}

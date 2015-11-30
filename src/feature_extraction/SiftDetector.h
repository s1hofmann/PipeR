//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "FeatureExtractionStep.h"
#include "SiftConfigContainer.h"
#include "../pipeline/return_codes.h"

namespace pipe {

class SiftDetector : public FeatureExtractionStep {
public:
    SiftDetector(const cv::Ptr<SiftConfigContainer> config,
                 const std::string &info = "SIFT feature extractor");

    virtual ~SiftDetector();

    virtual cv::Mat train(const cv::Mat &input, const cv::Mat &mask) const;
    virtual cv::Mat run(const cv::Mat &input, const cv::Mat &mask) const;
};


}

//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "FeatureExtractionStep.h"
#include "SiftConfigContainer.h"
#include "../pipeline/return_codes.h"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace pipe {

class SiftDetector : public FeatureExtractionStep {
public:
    SiftDetector(const cv::Ptr<SiftConfigContainer> config,
                 const std::string &info = "SIFT feature extractor");

    virtual ~SiftDetector();

    virtual cv::Mat train(const cv::Mat &input, const cv::Mat &mask) const;
    virtual cv::Mat run(const cv::Mat &input, const cv::Mat &mask) const;
    virtual cv::Mat debugTrain(const cv::Mat &input, const cv::Mat &mask) const;
    virtual cv::Mat debugRun(const cv::Mat &input, const cv::Mat &mask) const;

private:
};


}

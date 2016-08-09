#pragma once

#include "featuredetectionstep.h"
#include "SiftDetectorConfig.h"
#include "../exception/error.h"

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>


namespace pl {


class SiftDetector : public FeatureDetectionStep
{
public:
    SiftDetector(cv::Ptr<ConfigContainer> config);
    virtual ~SiftDetector();

    // FeatureDetectionStep interface
    std::vector<cv::KeyPoint> detect(const cv::Mat &input, const cv::Mat &mask) const;
    std::vector<cv::KeyPoint> debugDetect(const cv::Mat &input, const cv::Mat &mask) const;
};


}

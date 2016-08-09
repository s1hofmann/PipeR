#pragma once

#include "../pipeline/PipelineStep.h"

namespace pl {


class FeatureDetectionStep : public PseudoPipelineStep
{
public:
    virtual std::vector<cv::KeyPoint> detect(const cv::Mat &input, const cv::Mat &mask) const = 0;
    virtual std::vector<cv::KeyPoint> debugDetect(const cv::Mat &input, const cv::Mat &mask) const = 0;

protected:
    FeatureDetectionStep(cv::Ptr<ConfigContainer> config);
    virtual ~FeatureDetectionStep();

private:
    std::vector<std::string> cvDetectors = {
        "SIFT"
    };
};


}

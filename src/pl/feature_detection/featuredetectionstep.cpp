#include "featuredetectionstep.h"

namespace pl {


std::vector<cv::KeyPoint> FeatureDetectionStep::detect(const cv::Mat &input, const cv::Mat &mask) const
{
    return this->detectImpl(false, input, mask);
}

std::vector<cv::KeyPoint> FeatureDetectionStep::debugDetect(const cv::Mat &input, const cv::Mat &mask) const
{
    return this->detectImpl(true, input, mask);
}

FeatureDetectionStep::FeatureDetectionStep(cv::Ptr<ConfigContainer> config)
    :
        PseudoPipelineStep(config)
{

}

FeatureDetectionStep::~FeatureDetectionStep()
{

}


}

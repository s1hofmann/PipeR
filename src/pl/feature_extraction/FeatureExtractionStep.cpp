//
// Created by Simon Hofmann on 16.11.15.
//

#include "FeatureExtractionStep.h"

namespace pl {


FeatureExtractionStep::FeatureExtractionStep(const cv::Ptr<ConfigContainer> config)
    :
        PseudoPipelineStep(config)
{

}


FeatureExtractionStep::~FeatureExtractionStep() {

}

cv::Mat FeatureExtractionStep::augment(cv::Mat &descriptor,
                                       std::vector<cv::KeyPoint> &keypoints) const
{
    cv::Mat1f coords(descriptor.rows, 2);

    for(size_t idx = 0; idx < descriptor.rows; ++idx) {
        coords.at<float>(idx, 0) = keypoints[idx].pt.x;
        coords.at<float>(idx, 1) = keypoints[idx].pt.y;
    }

    cv::Mat result;
    cv::hconcat(descriptor, coords, result);

    return result;
}


}

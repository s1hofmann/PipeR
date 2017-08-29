//
// Created by Simon Hofmann on 28.12.15.
//

#include "MLStep.h"

namespace pl {


MLStep::MLStep(const cv::Ptr<ConfigContainer> config)
    :
        PseudoPipelineStep(config)
{

}

cv::Mat1d MLStep::calculateWeights(const cv::Mat1d &labels) const
{
    //Count positive and negative samples
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(labels, &negativeLabel, &positiveLabel, NULL, NULL);
    double posCnt = std::count(labels.begin(), labels.end(), positiveLabel);
    double negCnt = std::count(labels.begin(), labels.end(), negativeLabel);

    //Compute reciprocal weights
    double posWeight = (posCnt > 0) ? labels.total() / (posCnt * 2) : 1;
    double negWeight = (negCnt > 0) ? labels.total() / (negCnt * 2) : 1;

    //Construct weight matrix
    size_t elems = std::max(labels.cols, labels.rows);
    cv::Mat1d weights(labels.size());

    for(size_t idx = 0; idx < elems; ++idx) {
        if(labels.at<int32_t>(idx) == positiveLabel) {
            weights.at<double>(idx) = posWeight;
        } else if(labels.at<int32_t>(idx) == negativeLabel) {
            weights.at<double>(idx) = negWeight;
        }
    }

    return weights;
}

MLStep::~MLStep()
{

}


}

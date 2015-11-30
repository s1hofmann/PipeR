//
// Created by Simon Hofmann on 17.11.15.
//

#include <iostream>
#include <typeinfo>
#include "SiftDetector.h"


namespace pipe {


SiftDetector::SiftDetector(const cv::Ptr<SiftConfigContainer> config,
                           const std::string &info)
    :
        FeatureExtractionStep(config,
                              info)
{

}


SiftDetector::~SiftDetector()
{

}


cv::Mat SiftDetector::train(const cv::Mat &input, const cv::Mat &mask) const {
    cv::Mat result;

    cv::Ptr<SiftConfigContainer> maskConfig;
    maskConfig = this->mConfig.dynamicCast<SiftConfigContainer>();
}


cv::Mat SiftDetector::run(const cv::Mat &input, const cv::Mat &mask) const {
    return train(input, mask);
}
}

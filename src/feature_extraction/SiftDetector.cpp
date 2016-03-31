//
// Created by Simon Hofmann on 17.11.15.
//

#include <iostream>
#include <typeinfo>
#include "SiftDetector.h"


namespace pl {


SiftDetector::SiftDetector(const cv::Ptr<SiftConfigContainer> config)
    :
        FeatureExtractionStep(config)
{
}


SiftDetector::~SiftDetector()
{

}


cv::Mat SiftDetector::train(const cv::Mat &input, const cv::Mat &param) const {
    cv::Mat workingCopy;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
    } else {
        workingCopy = input;
    }

    cv::Ptr<SiftConfigContainer> extractorConfig;
    extractorConfig = this->mConfig.dynamicCast<SiftConfigContainer>();

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(extractorConfig->getBestFeatures(),
                                                                             extractorConfig->getOctaves(),
                                                                             extractorConfig->getContrastThresh(),
                                                                             extractorConfig->getEdgeThresh(),
                                                                             extractorConfig->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints);

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    return result;
}


cv::Mat SiftDetector::run(const cv::Mat &input, const cv::Mat &param) const {
    cv::Mat workingCopy;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
        debug("Incompatible type of input data, converting.");
    } else {
        workingCopy = input;
    }

    cv::Ptr<SiftConfigContainer> extractorConfig;
    extractorConfig = this->mConfig.dynamicCast<SiftConfigContainer>();

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(extractorConfig->getBestFeatures(),
                                                                             extractorConfig->getOctaves(),
                                                                             extractorConfig->getContrastThresh(),
                                                                             extractorConfig->getEdgeThresh(),
                                                                             extractorConfig->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints);
    debug(keypoints.size(), " keypoints detected.");

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    return result;
}


cv::Mat SiftDetector::debugTrain(const cv::Mat &input, const cv::Mat &param) const {
    return this->train(input, param);
}


cv::Mat SiftDetector::debugRun(const cv::Mat &input, const cv::Mat &param) const {
    return this->debugTrain(input, param);
}


}

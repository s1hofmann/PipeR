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
    cv::Mat mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8U) {
        param.convertTo(mask, CV_8U);
    } else {
        mask = param;
    }

    cv::Ptr<SiftConfigContainer> extractorConfig;
    extractorConfig = this->mConfig.dynamicCast<SiftConfigContainer>();

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(extractorConfig->getBestFeatures(),
                                                                             extractorConfig->getOctaves(),
                                                                             extractorConfig->getContrastThresh(),
                                                                             extractorConfig->getEdgeThresh(),
                                                                             extractorConfig->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    if(!param.empty()) {
        extractor->detect(workingCopy, keypoints, mask);
    } else {
        extractor->detect(workingCopy, keypoints);
    }

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(extractorConfig->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


cv::Mat SiftDetector::run(const cv::Mat &input, const cv::Mat &param) const {
    cv::Mat workingCopy;
    cv::Mat mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8U) {
        param.convertTo(mask, CV_8U);
    } else {
        mask = param;
    }

    cv::Ptr<SiftConfigContainer> extractorConfig;
    extractorConfig = this->mConfig.dynamicCast<SiftConfigContainer>();

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(extractorConfig->getBestFeatures(),
                                                                             extractorConfig->getOctaves(),
                                                                             extractorConfig->getContrastThresh(),
                                                                             extractorConfig->getEdgeThresh(),
                                                                             extractorConfig->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints, mask);

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(extractorConfig->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


cv::Mat SiftDetector::debugTrain(const cv::Mat &input, const cv::Mat &param) const {
    cv::Mat workingCopy;
    cv::Mat mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
        debug("Incompatible type of input data, converting.");
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8U) {
        param.convertTo(mask, CV_8U);
        debug("Incompatible type of mask data, converting.");
    } else {
        mask = param;
    }

    cv::Ptr<SiftConfigContainer> extractorConfig;
    extractorConfig = this->mConfig.dynamicCast<SiftConfigContainer>();

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(extractorConfig->getBestFeatures(),
                                                                             extractorConfig->getOctaves(),
                                                                             extractorConfig->getContrastThresh(),
                                                                             extractorConfig->getEdgeThresh(),
                                                                             extractorConfig->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints, mask);
    debug(keypoints.size(), " keypoints detected.");

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(extractorConfig->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


cv::Mat SiftDetector::debugRun(const cv::Mat &input, const cv::Mat &param) const {
    cv::Mat workingCopy;
    cv::Mat mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
        debug("Incompatible type of input data, converting.");
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8U) {
        param.convertTo(mask, CV_8U);
        debug("Incompatible type of mask data, converting.");
    } else {
        mask = param;
    }

    cv::Ptr<SiftConfigContainer> extractorConfig;
    extractorConfig = this->mConfig.dynamicCast<SiftConfigContainer>();

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(extractorConfig->getBestFeatures(),
                                                                             extractorConfig->getOctaves(),
                                                                             extractorConfig->getContrastThresh(),
                                                                             extractorConfig->getEdgeThresh(),
                                                                             extractorConfig->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints, mask);
    debug(keypoints.size(), " keypoints detected.");

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(extractorConfig->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


}

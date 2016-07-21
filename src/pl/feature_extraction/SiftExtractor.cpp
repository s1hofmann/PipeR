//
// Created by Simon Hofmann on 17.11.15.
//

#include <iostream>
#include <typeinfo>
#include "SiftExtractor.h"


namespace pl {


SiftExtractor::SiftExtractor(const cv::Ptr<ConfigContainer> config)
    :
        FeatureExtractionStep(config)
{
}


SiftExtractor::~SiftExtractor()
{

}


cv::Mat SiftExtractor::train(const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<SiftExtractorConfig> config;
    try {
        config = config_cast<SiftExtractorConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw FeatureExError(s.str(), currentMethod, currentLine);
    }

    cv::Mat workingCopy;
    cv::Mat1b mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8UC1) {
        param.convertTo(mask, CV_8UC1);
    } else {
        mask = param;
    }

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(config->getBestFeatures(),
                                                                             config->getOctaves(),
                                                                             config->getContrastThresh(),
                                                                             config->getEdgeThresh(),
                                                                             config->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    if(!param.empty()) {
        extractor->detect(workingCopy, keypoints, mask);
    } else {
        extractor->detect(workingCopy, keypoints);
    }

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(config->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


cv::Mat SiftExtractor::run(const cv::Mat &input, const cv::Mat &param) const {
    cv::Ptr<SiftExtractorConfig> config;
    try {
        config = config_cast<SiftExtractorConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw FeatureExError(s.str(), currentMethod, currentLine);
    }

    cv::Mat workingCopy;
    cv::Mat1b mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8UC1) {
        param.convertTo(mask, CV_8UC1);
    } else {
        mask = param;
    }

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(config->getBestFeatures(),
                                                                             config->getOctaves(),
                                                                             config->getContrastThresh(),
                                                                             config->getEdgeThresh(),
                                                                             config->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints, mask);

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(config->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


cv::Mat SiftExtractor::debugTrain(const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<SiftExtractorConfig> config;
    try {
        config = config_cast<SiftExtractorConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw FeatureExError(s.str(), currentMethod, currentLine);
    }

    cv::Mat workingCopy;
    cv::Mat1b mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
        debug("Incompatible type of input data, converting.");
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8UC1) {
        param.convertTo(mask, CV_8UC1);
        debug("Incompatible type of mask data, converting.");
    } else {
        mask = param;
    }

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(config->getBestFeatures(),
                                                                             config->getOctaves(),
                                                                             config->getContrastThresh(),
                                                                             config->getEdgeThresh(),
                                                                             config->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints, mask);
    debug(keypoints.size(), " keypoints detected.");

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(config->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


cv::Mat SiftExtractor::debugRun(const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<SiftExtractorConfig> config;
    try {
        config = config_cast<SiftExtractorConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw FeatureExError(s.str(), currentMethod, currentLine);
    }

    cv::Mat workingCopy;
    cv::Mat1b mask;

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
        debug("Incompatible type of input data, converting.");
    } else {
        workingCopy = input;
    }

    if(param.type() != CV_8UC1) {
        param.convertTo(mask, CV_8UC1);
        debug("Incompatible type of mask data, converting.");
    } else {
        mask = param;
    }

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(config->getBestFeatures(),
                                                                             config->getOctaves(),
                                                                             config->getContrastThresh(),
                                                                             config->getEdgeThresh(),
                                                                             config->getSigma());

    std::vector<cv::KeyPoint> keypoints;
    extractor->detect(workingCopy, keypoints, mask);
    debug(keypoints.size(), " keypoints detected.");

    cv::Mat result;
    extractor->compute(workingCopy, keypoints, result);

    if(config->augment()) {
        return augment(result, keypoints);
    } else {
        return result;
    }
}


}

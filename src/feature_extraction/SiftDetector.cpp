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


cv::Mat SiftDetector::train(const std::vector<cv::Mat> &input, const cv::Mat &mask) const {
    cv::Mat allDescriptors;

    for(cv::Mat in : input) {
        cv::Mat workingCopy;

        if(in.channels() > 1) {
            cv::cvtColor(in, workingCopy, cv::COLOR_BGR2GRAY);
        } else {
            workingCopy = in;
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

        allDescriptors.push_back(result);
    }

    return allDescriptors;
}


cv::Mat SiftDetector::run(const cv::Mat &input, const cv::Mat &mask) const {
    return this->train(input, mask);
}


cv::Mat SiftDetector::debugTrain(const std::vector<cv::Mat> &input, const cv::Mat &mask) const {
    return this->train(input, mask);
}


cv::Mat SiftDetector::debugRun(const cv::Mat &input, const cv::Mat &mask) const {
    return this->debugTrain(input, mask);
}


}

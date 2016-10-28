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

cv::Mat SiftExtractor::computeImpl(const bool debugMode, const cv::Mat &input, std::vector<cv::KeyPoint> &keypoints) const
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

    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
        if(debugMode) { debug("Incompatible type of input data, converting."); }
    } else {
        workingCopy = input;
    }

    cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SIFT::create(config->bestFeatures(),
                                                                             config->octaves(),
                                                                             config->contrastThresh(),
                                                                             config->edgeThresh(),
                                                                             config->sigma());

    if(!keypoints.empty()) {
        cv::Mat result;
        extractor->compute(workingCopy, keypoints, result);
        if(config->augment()) {
            return augment(result, keypoints);
        } else {
            return result;
        }
    }

    return cv::Mat();
}

cv::Mat SiftExtractor::computeImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &mask) const
{
    throw FeatureExError("SiftExtractor requires keypoints as input.", currentMethod, currentLine);
}


}

//
// Created by Simon Hofmann on 17.11.15.
//

#include <iostream>
#include "SiftDetector.h"


namespace pipe {


SiftDetector::SiftDetector(const cv::Ptr<SiftConfigContainer> config,
                           const std::string &info)
    :
        FeatureExtractionStep(config,
                              info)
{
    std::cout << config->bestFeatures() << std::endl;
}


SiftDetector::~SiftDetector() {

}


cv::Mat SiftDetector::train() {
    return cv::Mat();
}


cv::Mat SiftDetector::run() {
    return cv::Mat();
}


}

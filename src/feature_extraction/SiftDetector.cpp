//
// Created by Simon Hofmann on 17.11.15.
//

#include "SiftDetector.h"


namespace pipe {


SiftDetector::SiftDetector(const std::string &info,
                           const std::string &usage,
                           const std::string &help)
    :
        FeatureExtractionStep(info, usage, help)
{

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

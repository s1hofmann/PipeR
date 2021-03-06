#include "siftdetector.h"

namespace pl {


SiftDetector::SiftDetector(cv::Ptr<ConfigContainer> config)
    :
        FeatureDetectionStep(config)
{

}


SiftDetector::~SiftDetector()
{

}

std::vector<cv::KeyPoint> SiftDetector::detectImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &mask) const
{
    cv::Ptr<SiftDetectorConfig> config;
    try {
        config = config_cast<SiftDetectorConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw FeatureExError(s.str(), currentMethod, currentLine);
    }

    cv::Ptr<cv::xfeatures2d::SiftFeatureDetector> detector = cv::xfeatures2d::SiftFeatureDetector::create(config->bestFeatures(),
                                                                                                          config->octaves(),
                                                                                                          config->contrastThresh(),
                                                                                                          config->edgeThresh(),
                                                                                                          config->sigma());

    std::vector<cv::KeyPoint> keypoints;
    detector->detect(input, keypoints);

    if(debugMode) { debug("Detected ", keypoints.size(), " keypoints."); }

    return keypoints;
}


}

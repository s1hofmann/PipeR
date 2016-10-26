//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "FeatureExtractionStep.h"
#include "SiftExtractorConfig.h"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace pl {


/**
 * @brief The SiftDetector class
 */
class SiftExtractor : public FeatureExtractionStep {
public:
    /**
     * @brief SiftDetector
     * @param config
     * @param info
     */
    SiftExtractor(const cv::Ptr<ConfigContainer> config);

    /**
     * @brief ~SiftDetector
     */
    virtual ~SiftExtractor();

    // FeatureExtractionStep interface
    virtual cv::Mat computeImpl(const bool debugMode,
                                const cv::Mat &input,
                                std::vector<cv::KeyPoint> &keypoints) const override;

    virtual cv::Mat computeImpl(const bool debugMode,
                                const cv::Mat &input,
                                const cv::Mat &mask) const override;

private:
};


}

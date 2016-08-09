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

    /**
     * @brief compute
     * @param input
     * @param keypoints
     * @return
     */
    virtual cv::Mat compute(const cv::Mat &input,
                            std::vector<cv::KeyPoint> &keypoints) const override;

    /**
     * @brief debugCompute
     * @param input
     * @param keypoints
     * @return
     */
    virtual cv::Mat debugCompute(const cv::Mat &input,
                                 std::vector<cv::KeyPoint> &keypoints) const override;

private:

};


}

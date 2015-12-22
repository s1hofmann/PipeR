//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "FeatureExtractionStep.h"
#include "SiftConfigContainer.h"
#include "../pipeline/return_codes.h"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace pipe {


/**
 * @brief The SiftDetector class
 */
class SiftDetector : public FeatureExtractionStep {
public:
    /**
     * @brief SiftDetector
     * @param config
     * @param info
     */
    SiftDetector(const cv::Ptr<SiftConfigContainer> config,
                 const std::string &info = "SIFT feature extractor");

    /**
     * @brief ~SiftDetector
     */
    virtual ~SiftDetector();

    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask = cv::Mat()) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask = cv::Mat()) const;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &mask = cv::Mat()) const;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask = cv::Mat()) const;

private:
};


}

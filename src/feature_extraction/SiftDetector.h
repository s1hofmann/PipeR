//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "FeatureExtractionStep.h"
#include "SiftConfigContainer.h"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace pl {


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
    SiftDetector(const cv::Ptr<SiftConfigContainer> config);

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
                          const cv::Mat &param = cv::Mat()) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param = cv::Mat()) const;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const;

private:
};


}

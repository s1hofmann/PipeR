//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"


namespace pl {


/**
 * @brief The FeatureExtractionStep class
 */
class FeatureExtractionStep : public PipelineStep {
public:
    /**
     * @brief train
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief run
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief debugTrain
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief debugRun
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const = 0;

protected:
    /**
     * @brief FeatureExtractionStep
     * @param config
     * @param info
     */
    FeatureExtractionStep(const cv::Ptr<ConfigContainer> config);

    /**
     * @brief ~FeatureExtractionStep
     */
    virtual ~FeatureExtractionStep();

    cv::Mat augment(cv::Mat &descriptor, std::vector<cv::KeyPoint> &keypoints) const;
};


}


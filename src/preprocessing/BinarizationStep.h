//
// Created by Simon Hofmann on 13.12.15.
//


#pragma once

#include "PreprocessingStep.h"

namespace pipe {


class BinarizationStep : public PreprocessingStep {
public:
    BinarizationStep(const cv::Ptr<ConfigContainer> config,
                     const std::string &info = "Binarization preprocessing step");

    virtual ~BinarizationStep();

    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &mask) const;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask) const;
};


}

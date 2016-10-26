//
// Created by Simon Hofmann on 13.12.15.
//


#pragma once

#include "PreprocessingStep.h"
#include <iostream>

namespace pl {


class BinarizationStep : public PreprocessingStep {
public:
    BinarizationStep(const cv::Ptr<ConfigContainer> config);

    virtual ~BinarizationStep();

    // PipelineStep interface
    /**
     * @brief runImpl
     * @param debugMode
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat runImpl(const bool debugMode,
                            const cv::Mat &input,
                            const cv::Mat &param) const override;


    /**
     * @brief trainImpl
     * @param debugMode
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &param) const override;
};


}

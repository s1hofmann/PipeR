//
// Created by Simon Hofmann on 16.11.15.
//

#pragma once

#include "../pipeline/PipelineStep.h"
#include "../masks/MaskGenerator.h"

namespace pl {


/**
 * @brief The PreprocessingStep class
 */
class PreprocessingStep : public PipelineStep {
public:
    /**
     * @brief runImpl
     * @param debugMode
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat runImpl(const bool debugMode,
                            const cv::Mat &input,
                            const cv::Mat &param) const = 0;


    /**
     * @brief trainImpl
     * @param debugMode
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &param) const = 0;

protected:
    /**
     * @brief PreprocessingStep
     * @param config
     * @param info
     */
    PreprocessingStep(const cv::Ptr<ConfigContainer> config);

    /**
     * @brief ~PreprocessingStep
     */
    virtual ~PreprocessingStep();
};


}

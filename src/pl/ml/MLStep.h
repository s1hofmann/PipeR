//
// Created by Simon Hofmann on 28.12.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"

#include <opencv2/core/core.hpp>


namespace pl {


class MLStep : public PipelineStep {
public:
    // PipelineStep interface
    virtual cv::Mat runImpl(const bool debugMode,
                            const cv::Mat &input,
                            const cv::Mat &param) const = 0;

    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &param) const = 0;

protected:
    MLStep(const cv::Ptr<ConfigContainer> config);

    cv::Mat1d calculateWeights(const cv::Mat1d &labels) const;

    virtual ~MLStep();
};


}

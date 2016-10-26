//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"

namespace pl {


class DimensionalityReductionStep : public PipelineStep {
public:
    virtual cv::Mat runImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const = 0;

    virtual cv::Mat trainImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const = 0;
protected:
    DimensionalityReductionStep(const cv::Ptr<ConfigContainer> config);

    virtual ~DimensionalityReductionStep();
};


}

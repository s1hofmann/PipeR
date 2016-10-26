#pragma once

#include "DimensionalityReductionStep.h"
#include "PCAConfig.h"
#include "../core/dim/rpca.h"

#include <opencv2/core/core.hpp>

namespace pl {


class PCAStep : public DimensionalityReductionStep
{
public:
    PCAStep(const cv::Ptr<ConfigContainer> config);

    virtual ~PCAStep();

    // PipelineStep interface
    virtual cv::Mat runImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const;
    virtual cv::Mat trainImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const;
};


}

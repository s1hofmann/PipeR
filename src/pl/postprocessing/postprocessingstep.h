#pragma once

#include "../pipeline/PipelineStep.h"
#include "../pipeline/PipelineConfig.h"

namespace pl {


class PostProcessingStep : public PipelineStep
{
public:
    // PipelineStep interface
    virtual cv::Mat runImpl(const bool debugMode,
                            const cv::Mat &input,
                            const cv::Mat &param) const = 0;
    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &param) const = 0;
protected:
    PostProcessingStep(const cv::Ptr<ConfigContainer> config);

    virtual ~PostProcessingStep();


    // PipelineStep interface
public:
};


}

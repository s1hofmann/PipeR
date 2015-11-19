//
// Created by Simon Hofmann on 16.11.15.
//

#pragma once

#include "../pipeline/PipelineStep.h"

namespace pipe {


class PreprocessingStep : public PipelineStep {
public:
    PreprocessingStep(const cv::Ptr<ConfigContainer> config,
                      const std::string &info = std::string());

    virtual ~PreprocessingStep();

    virtual cv::Mat train() = 0;
    virtual cv::Mat run() = 0;
};


}

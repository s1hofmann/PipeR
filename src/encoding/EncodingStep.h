//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"

namespace pl {


class EncodingStep : public PipelineStep {
public:
    EncodingStep(const std::string &info = "Encoding step",
                 const std::string &usage = "Parameters go here.",
                 const std::string &help = "Detailed description goes here.");

    virtual ~EncodingStep();

    virtual cv::Mat train() = 0;
    virtual cv::Mat run() = 0;

private:
    std::string usage;
    std::string helpText;

    std::string name;
};


}

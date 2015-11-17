//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"


namespace pipe {


class FeatureExtractionStep : public PipelineStep {
public:
    FeatureExtractionStep(const std::string &info = "Feature extraction step",
                          const std::string &usage = "Parameters go here.",
                          const std::string &help = "Detailed description goes here.");

    virtual ~FeatureExtractionStep();

    virtual cv::Mat train() = 0;
    virtual cv::Mat run() = 0;

private:
    std::string usage;
    std::string helpText;

    std::string name;
};


}


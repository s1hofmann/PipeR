//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"


namespace pipe {


class FeatureExtractionStep : public PipelineStep {
public:
    FeatureExtractionStep(const cv::Ptr<ConfigContainer> config,
                          const std::string &info = "Feature extraction step");

    virtual ~FeatureExtractionStep();

    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const = 0;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const = 0;

private:
};


}


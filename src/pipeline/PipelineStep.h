//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <string>
#include <opencv2/core/core.hpp>

#include "ConfigContainer.h"

namespace pipe {


class PipelineStep {
public:
    PipelineStep(const cv::Ptr<ConfigContainer> config,
                 const std::string &info = std::string());

    virtual ~PipelineStep();

    virtual cv::Mat train() = 0;
    virtual cv::Mat run() = 0;

    std::string info();

    std::string help();
    std::string usage();

private:
    std::string mName;
    cv::Ptr<ConfigContainer> mConfig;
};


}


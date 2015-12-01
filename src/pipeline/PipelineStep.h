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

    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const = 0;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const = 0;

    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &mask) const = 0;

    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask) const = 0;

    std::string info();

    std::string help();
    std::string usage();

    std::string config() const;

protected:
    cv::Ptr<ConfigContainer> mConfig;
    std::string mName;

private:
};


}


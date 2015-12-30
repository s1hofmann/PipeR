#pragma once

#include "MLStep.h"

#include <opencv2/core/core.hpp>

namespace pl {


class SGDStep : public MLStep
{
public:
    SGDStep(const cv::Ptr<ConfigContainer> config,
            const std::string &info = "SGD solver");

    virtual ~SGDStep();

    // PipelineStep interface
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param = cv::Mat()) const;

    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const;

    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param = cv::Mat()) const;

    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const;
};


}

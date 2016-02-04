//
// Created by Simon Hofmann on 28.12.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"

#include <opencv2/core/core.hpp>


namespace pl {


class MLStep : public PipelineStep {
public:
    // PipelineStep interface
    cv::Mat train(const cv::Mat &input,
                  const cv::Mat &mask = cv::Mat()) const = 0;

    cv::Mat run(const cv::Mat &input,
                const cv::Mat &mask = cv::Mat()) const = 0;

    cv::Mat debugTrain(const cv::Mat &input,
                       const cv::Mat &mask = cv::Mat()) const = 0;

    cv::Mat debugRun(const cv::Mat &input,
                     const cv::Mat &mask = cv::Mat()) const = 0;

protected:
    MLStep(const cv::Ptr<ConfigContainer> config);

    cv::Mat1d calculateWeights(const cv::Mat1d &labels) const;

    virtual ~MLStep();
};


}

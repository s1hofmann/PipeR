#pragma once

#include "MLStep.h"

#include <opencv2/core/core.hpp>
#include "../core/vlfeat/wrapper/sgdsolver.h"
#include "SGDConfig.h"

#include <iostream>

namespace pl {


class SGDStep : public MLStep
{
public:
    SGDStep(const cv::Ptr<SGDConfig> config,
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

private:
    cv::Mat1d load(const std::string &fileName);
    void save(const std::string &fileName,
              const cv::Mat1d &model,
              const cv::Mat1d &bias);
};


}

#pragma once

#include "MLStep.h"

#include <opencv2/core/core.hpp>
#include "../core/vlfeat/wrapper/sgdsolver.h"
#include "SGDConfig.h"

#include <iostream>
#include <utility>

namespace pl {


class SGDStep : public MLStep
{
public:
    SGDStep(const cv::Ptr<SGDConfig> config);

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
    /**
     * @brief load Loads classifier data from a given file
     * @param fileName Filename to load data from
     * @return \link{std::pair} of \link{cv::Mat1d} and double, the first storing model parameters, the latter holds the bias term
     */
    std::pair<cv::Mat1d, double> load(const std::string &fileName) const;

    /**
     * @brief save Saves classifier data to given file
     * @param fileName Output file
     * @param model \link{cv::Mat1d} containing the classifier parameters
     * @param bias Bias value
     */
    void save(const std::string &fileName,
              const cv::Mat1d &model,
              const double bias) const;
};


}

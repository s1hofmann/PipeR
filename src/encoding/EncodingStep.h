//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"
#include "../pipeline/ConfigContainer.h"

namespace pl {


class EncodingStep : public PipelineStep {
public:
    /**
     * @brief train
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief run
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief debugTrain
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief debugRun
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const = 0;

protected:
    EncodingStep(const cv::Ptr<ConfigContainer> config);

    virtual ~EncodingStep();
};


}

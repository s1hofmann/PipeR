//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>

#include "globals.h"
#include "../exception/error.h"

#include "ConfigContainer.h"

namespace pl {


class PipelineStep {
public:
    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param= cv::Mat()) const = 0;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const = 0;

    /**
     * @brief info
     * @return
     */
    std::string info();

    /**
     * @brief help
     * @return
     */
    std::string help();

    /**
     * @brief usage
     * @return
     */
    std::string usage();

    /**
     * @brief config
     * @return
     */
    std::string config() const;

    /**
     * @brief id
     * @return
     */
    std::string identifier() const;

    /**
     * @brief mConfig
     */
    cv::Ptr<ConfigContainer> mConfig;

protected:
    /**
     * @brief PipelineStep
     * @param config
     * @param info
     */
    PipelineStep(const cv::Ptr<ConfigContainer> config);

    /**
     * @brief ~PipelineStep
     */
    virtual ~PipelineStep();

private:
};


class PseudoPipelineStep {
public:
    /**
     * @brief info
     * @return
     */
    std::string info();

    /**
     * @brief help
     * @return
     */
    std::string help();

    /**
     * @brief usage
     * @return
     */
    std::string usage();

    /**
     * @brief config
     * @return
     */
    std::string config() const;

    /**
     * @brief id
     * @return
     */
    std::string identifier() const;

    /**
     * @brief mConfig
     */
    cv::Ptr<ConfigContainer> mConfig;

protected:
    /**
     * @brief PipelineStep
     * @param config
     * @param info
     */
    PseudoPipelineStep(const cv::Ptr<ConfigContainer> config);

    /**
     * @brief ~PipelineStep
     */
    virtual ~PseudoPipelineStep();

private:
};


}


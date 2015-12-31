//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>

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

protected:
    /**
     * @brief PipelineStep
     * @param config
     * @param info
     */
    PipelineStep(const cv::Ptr<ConfigContainer> config,
                 const std::string &info = std::string());

    /**
     * @brief ~PipelineStep
     */
    virtual ~PipelineStep();

    /**
     * @brief mConfig
     */
    cv::Ptr<ConfigContainer> mConfig;

    /**
     * @brief mName
     */
    std::string mName;

    /**
     * @brief log
     * @param text
     */
    virtual void log(const std::string &text) const;

    /**
     * @brief warning
     * @param text
     */
    virtual void warning(const std::string &text) const;

    /**
     * @brief debug
     * @param text
     */
    virtual void debug(const std::string &text) const;

private:
};


}


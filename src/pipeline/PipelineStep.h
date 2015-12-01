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

    //TODO Additional train and run methods which take a cv::Ptr to a MaskGeneration object instead of a mask cv::Mat object

    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const std::vector<cv::Mat> &input,
                          const cv::Mat &mask) const = 0;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const = 0;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const std::vector<cv::Mat> &input,
                               const cv::Mat &mask) const = 0;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask) const = 0;

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
     * @brief mConfig
     */
    cv::Ptr<ConfigContainer> mConfig;

    /**
     * @brief mName
     */
    std::string mName;

private:
};


}


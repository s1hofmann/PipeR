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

private:
};


}


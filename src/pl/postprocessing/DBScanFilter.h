//
// Created by Simon Hofmann on 22.07.16.
//


#pragma once

#include "postprocessingstep.h"
#include "DBScanConfig.h"
#include "../core/clustering/dbscan.h"

namespace pl {


class DBScanFilter: public PostProcessingStep {
public:
    DBScanFilter(const cv::Ptr<ConfigContainer> config);

    virtual ~DBScanFilter();

    /**
     * @brief runImpl
     * @param debug
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat runImpl(const bool debugMode,
                            const cv::Mat &input,
                            const cv::Mat &param) const override;


    /**
     * @brief trainImpl
     * @param debug
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &param) const override;

private:

    // PipelineStep interface
public:
};


}

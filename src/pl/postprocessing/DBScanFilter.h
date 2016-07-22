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
     * @brief train Performs DBSCAN clustering on augmented keypoints and neglects small clusters. Used to filter keypoints.
     * @param input cv::Mat containing augmented keypoints. Coordinates are assumed to be stored as (x,y) in the last to columns of the matrix.
     * @param param
     * @return Filtered keypoints, without augmentation
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param = cv::Mat()) const override;

    /**
     * @brief run
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const override;

    /**
     * @brief debugTrain
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param = cv::Mat()) const override;

    /**
     * @brief debugRun
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const override;

private:
};


}

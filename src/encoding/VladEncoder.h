//
// Created by Simon Hofmann on 18.11.15.
//


#pragma once

#include "EncodingStep.h"
#include "VladConfig.h"

#include "../core/clustering/kmeanscluster.h"
#include "../core/encoding/vladencoder.h"

#include "../io/FileUtil.h"

namespace pl {


class VladEncodingStep : public EncodingStep {
public:
    VladEncodingStep(const cv::Ptr<VladConfig> config);

    virtual ~VladEncodingStep();

    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param = cv::Mat()) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param = cv::Mat()) const;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const;

private:
};


}


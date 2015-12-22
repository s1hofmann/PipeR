#pragma once

#include "DimensionalityReductionStep.h"
#include "PCAConfig.h"
#include "../core/dim/rpca.h"

#include <opencv2/core/core.hpp>

namespace pl {


class PCAStep : public DimensionalityReductionStep
{
public:
    PCAStep(const cv::Ptr<PCAConfig> config,
            const std::string &info = "PCA");

    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask = cv::Mat()) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask = cv::Mat()) const;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &mask = cv::Mat()) const;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask = cv::Mat()) const;

    virtual ~PCAStep();
};


}

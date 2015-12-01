//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "PreprocessingStep.h"
#include "VesselMaskConfig.h"
#include "../core/vesselfilter.h"

namespace pipe {


/**
 * @brief The VesselMask class
 */
class VesselMask : public MaskGenerationStep {
public:
    /**
     * @brief VesselMask
     * @param config
     * @param info
     */
    VesselMask(const cv::Ptr<ConfigContainer> &config,
               const std::string &info = "Vesselness mask generation");

    /**
     * @brief ~VesselMask
     */
    virtual ~VesselMask();

    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &mask) const;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask) const;
private:
};


}

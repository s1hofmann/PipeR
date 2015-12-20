//
// Created by Simon Hofmann on 16.11.15.
//

#pragma once

#include "../pipeline/PipelineStep.h"
#include "../masks/MaskGenerator.h"

namespace pipe {


/**
 * @brief The PreprocessingStep class
 */
class PreprocessingStep : public PipelineStep {
public:
    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> train(const std::vector<cv::Mat> &input,
                                       const cv::Mat &mask) const = 0;

    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> train(const std::vector<cv::Mat> &input,
                                       const cv::Ptr<MaskGenerator> mask) const = 0;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> run(const cv::Mat &input,
                                     const cv::Mat &mask) const = 0;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> run(const cv::Mat &input,
                                     const cv::Ptr<MaskGenerator> mask) const = 0;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> debugTrain(const std::vector<cv::Mat> &input,
                                            const cv::Mat &mask) const = 0;

    /**
     * @brief debugTrain
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> debugTrain(const std::vector<cv::Mat> &input,
                                            const cv::Ptr<MaskGenerator> mask) const = 0;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> debugRun(const cv::Mat &input,
                                          const cv::Mat &mask) const = 0;

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual std::vector<cv::Mat> debugRun(const cv::Mat &input,
                                          const cv::Ptr<MaskGenerator> mask) const = 0;

protected:
    /**
     * @brief PreprocessingStep
     * @param config
     * @param info
     */
    PreprocessingStep(const cv::Ptr<ConfigContainer> config,
                      const std::string &info = "Preprocessing step");

    /**
     * @brief ~PreprocessingStep
     */
    virtual ~PreprocessingStep();
};


}

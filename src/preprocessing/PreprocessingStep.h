//
// Created by Simon Hofmann on 16.11.15.
//

#pragma once

#include "../pipeline/PipelineStep.h"

namespace pipe {


/**
 * @brief The PreprocessingStep class
 */
class PreprocessingStep : public PipelineStep {
public:
    /**
     * @brief PreprocessingStep
     * @param config
     * @param info
     */
    PreprocessingStep(const cv::Ptr<ConfigContainer> config,
                      const std::string &info = std::string());

    /**
     * @brief ~PreprocessingStep
     */
    virtual ~PreprocessingStep();

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
};


//TODO Move this into separate class MaskGenerator
class MaskGenerationStep : public PreprocessingStep {
public:
    MaskGenerationStep(const cv::Ptr<ConfigContainer> config,
                       const std::string &info = "Mask generation preprocessing method");

    virtual ~MaskGenerationStep();

    virtual cv::Mat train(const std::vector<cv::Mat> &input,
                          const cv::Mat &mask) const = 0;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const = 0;

    virtual cv::Mat debugTrain(const std::vector<cv::Mat> &input,
                               const cv::Mat &mask) const = 0;

    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask) const = 0;

private:

};


/**
 * @brief The ImageProcessingStep class
 */
class ImageProcessingStep : public PreprocessingStep {
public:
    ImageProcessingStep(const cv::Ptr<ConfigContainer> config,
                        const std::string &info = "Image preprocessing method");

    //FIXME: Should still be pure virtual, only for debugging
    /**
     * @brief train
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat train(const std::vector<cv::Mat> &input,
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
    virtual cv::Mat debugTrain(const std::vector<cv::Mat> &input,
                               const cv::Mat &mask) const {

    }

    /**
     * @brief debugRun
     * @param input
     * @param mask
     * @return
     */
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &mask) const {

    }

    virtual ~ImageProcessingStep();

private:

};


}

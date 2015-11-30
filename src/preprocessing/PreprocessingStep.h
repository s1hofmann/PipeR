//
// Created by Simon Hofmann on 16.11.15.
//

#pragma once

#include "../pipeline/PipelineStep.h"

namespace pipe {


class PreprocessingStep : public PipelineStep {
public:
    PreprocessingStep(const cv::Ptr<ConfigContainer> config,
                      const std::string &info = std::string());

    virtual ~PreprocessingStep();

    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const = 0;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const = 0;
};


class MaskGenerationStep : public PreprocessingStep {
public:
    MaskGenerationStep(const cv::Ptr<ConfigContainer> config,
                       const std::string &info = "Mask generation preprocessing method");

    virtual ~MaskGenerationStep();

    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const = 0;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const = 0;

private:

};


class ImageProcessingStep : public PreprocessingStep {
public:
    ImageProcessingStep(const cv::Ptr<ConfigContainer> config,
                        const std::string &info = "Image preprocessing method");

    //FIXME: Should still be pure virtual, only for debugging
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const;

    virtual ~ImageProcessingStep();

private:

};


}

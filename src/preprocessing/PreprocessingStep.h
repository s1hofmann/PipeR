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

    virtual cv::Mat train() = 0;
    virtual cv::Mat run() = 0;
};


class MaskGenerationStep : public PreprocessingStep {
public:
    MaskGenerationStep(const cv::Ptr<ConfigContainer> config,
                       const std::string &info = "Mask generation preprocessing method");

    virtual ~MaskGenerationStep();

    //FIXME: Should still be pure virtual, just for debugging
    virtual cv::Mat train();
    virtual cv::Mat run();

private:

};


class ImageProcessingStep : public PreprocessingStep {
public:
    ImageProcessingStep(const cv::Ptr<ConfigContainer> config,
                        const std::string &info = "Image preprocessing method");

    //FIXME: Should still be pure virtual, only for debugging
    virtual cv::Mat train();
    virtual cv::Mat run();

    virtual ~ImageProcessingStep();

private:

};


}

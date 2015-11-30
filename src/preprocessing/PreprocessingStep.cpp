//
// Created by Simon Hofmann on 16.11.15.
//

#include "PreprocessingStep.h"

namespace pipe {


PreprocessingStep::PreprocessingStep(const cv::Ptr<ConfigContainer> config,
                                     const std::string &info)
    :
        PipelineStep(config,
                     info)
{

}


PreprocessingStep::~PreprocessingStep()
{

}


ImageProcessingStep::ImageProcessingStep(const cv::Ptr<ConfigContainer> config,
                                         const std::string &info)
        :
        PreprocessingStep(config,
                          info)
{

}


ImageProcessingStep::~ImageProcessingStep()
{

}


cv::Mat ImageProcessingStep::train(const cv::Mat &input, const cv::Mat &mask) const
{
    return cv::Mat();
}


cv::Mat ImageProcessingStep::run(const cv::Mat &input, const cv::Mat &mask) const
{
    return cv::Mat();
}


MaskGenerationStep::MaskGenerationStep(const cv::Ptr<ConfigContainer> config,
                                       const std::string &info)
    :
        PreprocessingStep(config,
                          info)
{

}


MaskGenerationStep::~MaskGenerationStep()
{

}

}

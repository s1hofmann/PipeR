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


cv::Mat ImageProcessingStep::train()
{
    return cv::Mat();
}


cv::Mat ImageProcessingStep::run()
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


cv::Mat MaskGenerationStep::train()
{
    return cv::Mat();
}


cv::Mat MaskGenerationStep::run()
{
    return cv::Mat();
}


}

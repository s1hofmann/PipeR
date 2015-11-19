//
// Created by Simon Hofmann on 17.11.15.
//

#include "MaskGenerationStep.h"

namespace pipe {


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

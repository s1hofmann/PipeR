//
// Created by Simon Hofmann on 17.11.15.
//

#include "ImageProcessingStep.h"

namespace pipe {


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


}

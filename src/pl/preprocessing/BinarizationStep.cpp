//
// Created by Simon Hofmann on 13.12.15.
//

#include "BinarizationStep.h"

namespace pl {


BinarizationStep::BinarizationStep(const cv::Ptr<ConfigContainer> config)
    :
        PreprocessingStep(config)
{
}


BinarizationStep::~BinarizationStep()
{

}

cv::Mat BinarizationStep::runImpl(const bool debugMode,
                                  const cv::Mat &input,
                                  const cv::Mat &param) const
{
    return input;
}


cv::Mat BinarizationStep::trainImpl(const bool debugMode,
                                    const cv::Mat &input,
                                    const cv::Mat &param) const
{
    return input;
}


}

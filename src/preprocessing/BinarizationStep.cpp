//
// Created by Simon Hofmann on 13.12.15.
//

#include "BinarizationStep.h"

namespace pl {


BinarizationStep::BinarizationStep(const cv::Ptr<ConfigContainer> config,
                                   const std::string &info)
    :
        PreprocessingStep(config,
                          info)
{
}


BinarizationStep::~BinarizationStep()
{

}


cv::Mat BinarizationStep::train(const cv::Mat &input,
                                const cv::Mat &mask) const
{
    //TODO Implementation, obviously
}


cv::Mat BinarizationStep::run(const cv::Mat &input,
                              const cv::Mat &mask) const
{
    return this->train(input, mask);
}


cv::Mat BinarizationStep::debugTrain(const cv::Mat &input,
                                     const cv::Mat &mask) const
{
    std::cout << "Debug mode" << std::endl;
    return this->train(input, mask);
}


cv::Mat BinarizationStep::debugRun(const cv::Mat &input,
                                   const cv::Mat &mask) const
{
    std::cout << "Debug mode" << std::endl;
    return this->debugTrain(input, mask);
}


}

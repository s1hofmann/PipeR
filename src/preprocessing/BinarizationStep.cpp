//
// Created by Simon Hofmann on 13.12.15.
//

#include "BinarizationStep.h"

namespace pipe {


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


std::vector<cv::Mat> BinarizationStep::train(const std::vector<cv::Mat> &input,
                                             const cv::Mat &mask) const
{

}


std::vector<cv::Mat> BinarizationStep::train(const std::vector<cv::Mat> &input,
                                             const cv::Ptr<MaskGenerator> mask) const
{

}


std::vector<cv::Mat> BinarizationStep::run(const cv::Mat &input,
                                           const cv::Mat &mask) const
{

}


std::vector<cv::Mat> BinarizationStep::run(const cv::Mat &input,
                                           const cv::Ptr<MaskGenerator> mask) const
{

}


std::vector<cv::Mat> BinarizationStep::debugTrain(const std::vector<cv::Mat> &input,
                                                  const cv::Mat &mask) const
{

}


std::vector<cv::Mat> BinarizationStep::debugTrain(const std::vector<cv::Mat> &input,
                                                  const cv::Ptr<MaskGenerator> mask) const
{

}


std::vector<cv::Mat> BinarizationStep::debugRun(const cv::Mat &input,
                                                const cv::Mat &mask) const
{

}


std::vector<cv::Mat> BinarizationStep::debugRun(const cv::Mat &input,
                                                const cv::Ptr<MaskGenerator> mask) const
{

}


}

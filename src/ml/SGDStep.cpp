#include "SGDStep.h"


namespace pl {


SGDStep::SGDStep(const cv::Ptr<ConfigContainer> config,
                 const std::string &info)
    :
        MLStep(config,
               info)
{
}


SGDStep::~SGDStep()
{
}


cv::Mat SGDStep::train(const cv::Mat &input, const cv::Mat &param) const
{

}


cv::Mat SGDStep::run(const cv::Mat &input, const cv::Mat &param) const
{

}


cv::Mat SGDStep::debugTrain(const cv::Mat &input, const cv::Mat &param) const
{

}


cv::Mat SGDStep::debugRun(const cv::Mat &input, const cv::Mat &param) const
{

}


}

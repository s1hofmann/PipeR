#include "PCAStep.h"


namespace pipe {


PCAStep::PCAStep(const cv::Ptr<PCAConfig> config,
                 const std::string &info)
    :
        DimensionalityReductionStep(config,
                                    info)
{

}


cv::Mat PCAStep::train(const cv::Mat &input, const cv::Mat &mask) const
{
    //TODO: PCA fit
}


cv::Mat PCAStep::run(const cv::Mat &input, const cv::Mat &mask) const
{
    //TODO PCA transform
}


cv::Mat PCAStep::debugTrain(const cv::Mat &input, const cv::Mat &mask) const
{
    this->train();
}


cv::Mat PCAStep::debugRun(const cv::Mat &input, const cv::Mat &mask) const
{
    this->run();
}




PCAStep::~PCAStep()
{

}


}

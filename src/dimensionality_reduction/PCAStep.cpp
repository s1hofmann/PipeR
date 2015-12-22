#include "PCAStep.h"


namespace pipe {


PCAStep::PCAStep(const cv::Ptr<PCAConfig> config,
                 const std::string &info)
    :
        DimensionalityReductionStep(config,
                                    info)
{

}


cv::Mat PCAStep::train(const cv::Mat &input,
                       const cv::Mat &mask) const
{
    this->mConfig.dynamicCast<PCAConfig>()->getEpsilon();
    //TODO: PCA fit
}


cv::Mat PCAStep::run(const cv::Mat &input,
                     const cv::Mat &mask) const
{
    //TODO PCA transform
}


cv::Mat PCAStep::debugTrain(const cv::Mat &input,
                            const cv::Mat &mask) const
{
    this->train(input,
                mask);
}


cv::Mat PCAStep::debugRun(const cv::Mat &input,
                          const cv::Mat &mask) const
{
    this->run(input,
              mask);
}




PCAStep::~PCAStep()
{

}


}

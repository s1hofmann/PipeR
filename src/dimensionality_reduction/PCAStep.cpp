#include "PCAStep.h"


namespace pl {


PCAStep::PCAStep(const cv::Ptr<PCAConfig> config)
    :
        DimensionalityReductionStep(config)
{

}


cv::Mat PCAStep::train(const cv::Mat &input,
                       const cv::Mat &param) const
{
    int components = std::min(this->mConfig.dynamicCast<PCAConfig>()->getComponents(), input.cols);
    if(components <= 0) {
        components = input.cols;
    }
    double epsilon = this->mConfig.dynamicCast<PCAConfig>()->getEpsilon();
    bool whitening = this->mConfig.dynamicCast<PCAConfig>()->getWhitening();
    std::string path = this->mConfig.dynamicCast<PCAConfig>()->getPath();

    RPCA rpca(components,
              whitening,
              epsilon);

    rpca.fit(input);

    rpca.dump(path);

    cv::Mat1f result;
    rpca.transform(input,
                   result);

    return result;
}


cv::Mat PCAStep::run(const cv::Mat &input,
                     const cv::Mat &param) const
{
    std::string path = this->mConfig.dynamicCast<PCAConfig>()->getPath();

    RPCA rpca(path);

    cv::Mat1f result;
    rpca.transform(input,
                   result);

    return result;
}


cv::Mat PCAStep::debugTrain(const cv::Mat &input,
                            const cv::Mat &param) const
{
    return this->train(input,
                       param);
}


cv::Mat PCAStep::debugRun(const cv::Mat &input,
                          const cv::Mat &param) const
{
    return this->run(input,
                     param);
}




PCAStep::~PCAStep()
{

}


}

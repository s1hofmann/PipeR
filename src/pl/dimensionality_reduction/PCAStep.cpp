#include "PCAStep.h"


namespace pl {


PCAStep::PCAStep(const cv::Ptr<ConfigContainer> config)
    :
        DimensionalityReductionStep(config)
{

}

PCAStep::~PCAStep()
{

}

cv::Mat PCAStep::runImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<PCAConfig> config;
    try {
        config = config_cast<PCAConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw DimensionalityReductionError(s.str(), currentMethod, currentLine);
    }

    std::string path = config->path();

    RPCA rpca(path);

    cv::Mat1f result;
    try {
        rpca.transform(input,
                       result);
    } catch(DimensionalityReductionError) {
        throw;
    }

    return result;
}

cv::Mat PCAStep::trainImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<PCAConfig> config;
    try {
        config = config_cast<PCAConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw DimensionalityReductionError(s.str(), currentMethod, currentLine);
    }

    int components = std::min(config->components(), input.cols);
    if(components <= 0) {
        components = input.cols;
    }
    double epsilon = config->epsilon();
    bool whitening = config->whitening();
    std::string path = config->path();

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


}

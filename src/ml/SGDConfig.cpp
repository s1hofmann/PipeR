#include "SGDConfig.h"


namespace pl {


SGDConfig::SGDConfig(const std::__cxx11::string &outputFile, const double lambda,
                     const double bias,
                     const double learningRate,
                     const double multiplier,
                     const double epsilon,
                     vl_size iterations,
                     vl_size maxIterations)
    :
        ConfigContainer("SGD configuration",
                        "Not done yet..."),
        mClassifierFile(outputFile),
        mLambda(lambda),
        mBias(bias),
        mLearningRate(learningRate),
        mMultiplier(multiplier),
        mEpsilon(epsilon),
        mIterations(iterations),
        mMaxIterations(maxIterations)
{

}


SGDConfig::~SGDConfig()
{

}


double SGDConfig::lambda() const
{
    return mLambda;
}


void SGDConfig::setLambda(double lambda)
{
    mLambda = lambda;
}


double SGDConfig::learningRate() const
{
    return mLearningRate;
}


void SGDConfig::setLearningRate(double learningRate)
{
    mLearningRate = learningRate;
}


double SGDConfig::multiplier() const
{
    return mMultiplier;
}


void SGDConfig::setMultiplier(double multiplier)
{
    mMultiplier = multiplier;
}


double SGDConfig::epsilon() const
{
    return mEpsilon;
}


void SGDConfig::setEpsilon(double epsilon)
{
    mEpsilon = epsilon;
}


cv::Mat1d SGDConfig::model() const
{
    return mModel;
}


void SGDConfig::setModel(const cv::Mat1d &model)
{
    mModel = model;
}


double SGDConfig::bias() const
{
    return mBias;
}


void SGDConfig::setBias(double bias)
{
    mBias = bias;
}


vl_size SGDConfig::iterations() const
{
    return mIterations;
}


void SGDConfig::setIterations(const vl_size &iterations)
{
    mIterations = iterations;
}


vl_size SGDConfig::maxIterations() const
{
    return mMaxIterations;
}


void SGDConfig::setMaxIterations(const vl_size &maxIterations)
{
    mMaxIterations = maxIterations;
}


std::string SGDConfig::classifierFile() const
{
    return mClassifierFile;
}


void SGDConfig::setClassifierFile(const std::string &classifierFile)
{
    mClassifierFile = classifierFile;
}


std::string SGDConfig::toString() const
{
    std::stringstream configString;

    configString << "Classifier file: " << classifierFile()<< std::endl
                 << "Lambda: " << lambda() << std::endl
                 << "Learning rate: " << learningRate() << std::endl
                 << "Epsilon: " << epsilon() << std::endl
                 << "Bias: " << bias() << std::endl
                 << "Bias multiplier: " << multiplier() << std::endl
                 << "Iterations: " << iterations() << std::endl
                 << "Max. iterations: " << maxIterations() << std::endl
                 << "Model dimensions: " << mModel.rows << "x" << mModel.cols << std::endl;

    return configString.str();
}


}

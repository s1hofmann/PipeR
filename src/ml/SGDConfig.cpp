#include "SGDConfig.h"


namespace pl {


SGDConfig::SGDConfig(const std::string &identifier,
                     const std::string &outputFile,
                     const double lambda,
                     const double learningRate,
                     const double multiplier,
                     const double epsilon,
                     vl_size maxIterations)
    :
        ConfigContainer(identifier),
        mClassifierFile(outputFile),
        mLambda(lambda),
        mLearningRate(learningRate),
        mMultiplier(multiplier),
        mEpsilon(epsilon),
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
                 << "Bias multiplier: " << multiplier() << std::endl
                 << "Max. iterations: " << maxIterations() << std::endl;
    if(mModel.rows > 0 && mModel.cols > 0) {
        configString << "Model dimensions: " << mModel.rows << "x" << mModel.cols << std::endl;
    }

    return configString.str();
}

bool SGDConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mLambda = params.get(varName(mLambda), 0.001).asDouble();
        mLearningRate = params.get(varName(mLearningRate), 0.001).asDouble();
        mMultiplier = params.get(varName(mMultiplier), 1.0).asDouble();
        mEpsilon = params.get(varName(mEpsilon), 1e10-5).asDouble();
        mMaxIterations = params.get(varName(mMaxIterations), 10000).asInt();
        mClassifierFile = params.get(varName(mClassifierFile), "./trainedClassifier.yml").asString();

        return true;
    }
}


}

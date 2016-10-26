#include "SGDConfig.h"


namespace pl {


SGDConfig::SGDConfig(const std::string &identifier,
                     const std::vector<std::string> &outputFiles,
                     const double lambda,
                     const double learningRate,
                     const double multiplier,
                     const double epsilon,
                     vl_size iterations,
                     vl_size maxIterations,
                     const double bias,
                     const int folds,
                     const bool binary)
    :
        MLConfig(identifier, folds),
        mClassifierFiles(outputFiles),
        mLambda(lambda),
        mLearningRate(learningRate),
        mMultiplier(multiplier),
        mEpsilon(epsilon),
        mMaxIterations(maxIterations),
        mIterations(iterations),
        mBias(bias),
        mBinary(binary)
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


std::vector<std::string> SGDConfig::classifierFiles() const
{
    return mClassifierFiles;
}


void SGDConfig::setClassifierFiles(const std::vector<std::string> &classifierFiles)
{
    mClassifierFiles = classifierFiles;
}


std::string SGDConfig::toString() const
{
    std::stringstream configString;

    for(size_t idx = 0; idx < mClassifierFiles.size(); ++idx) {
        configString << "Classifier file: " << mClassifierFiles[idx] << std::endl;
    }

    configString << "Lambda: " << lambda() << std::endl
                 << "Bias multiplier: " << multiplier() << std::endl
                 << "Bias learning rate: " << learningRate() << std::endl;
    if(iterations()) {
        configString << "Starting iterations: " << iterations() << std::endl;
    }
    if(epsilon()) {
        configString << "Epsilon: " << epsilon() << std::endl;
    }
    if(maxIterations()) {
        configString << "Max. iterations: " << maxIterations() << std::endl;
    }
    if(mFolds > 1) {
        configString << mFolds << "-fold crossvalidation" << std::endl;
    }
    configString << "Binary classification: " << binary() << std::endl;

    return configString.str();
}

bool SGDConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mLambda = params.get(varName(mLambda), 0.0001).asDouble();
        mLearningRate = params.get(varName(mLearningRate), 1.0).asDouble();
        mMultiplier = params.get(varName(mMultiplier), 1.0).asDouble();
        mEpsilon = params.get(varName(mEpsilon), 0.0).asDouble();
        mIterations = params.get(varName(mIterations), 0).asUInt64();
        mMaxIterations = params.get(varName(mMaxIterations), 0).asUInt64();
        mBinary = params.get(varName(mBinary), false).asBool();
        mFolds = params.get(varName(mFolds), 5).asInt();

        const Json::Value classifiers = params[varName(mClassifierFiles)];

        if(classifiers.size()) {
            for(unsigned int idx = 0; idx < classifiers.size(); ++idx) {
                mClassifierFiles.push_back(classifiers[idx].asString());
            }
        } else {
            warning("No classifier file specified, using fallback value.");
            mClassifierFiles.push_back("./trainedClassifier.yml");
        }

        return true;
    }
}

bool SGDConfig::binary() const
{
    return mBinary;
}

void SGDConfig::setBinary(bool binary)
{
    mBinary = binary;
}


}

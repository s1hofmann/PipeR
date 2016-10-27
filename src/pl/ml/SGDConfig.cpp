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
                     const bool platt,
                     const bool binary)
    :
        MLConfig(identifier, folds),
        mClassifierFiles(outputFiles),
        mEpsilon(epsilon),
        mMaxIterations(maxIterations),
        mIterations(iterations),
        mBias(bias),
        mPlattScale(platt),
        mBinary(binary)
{
    mLambdas.push_back(lambda);
    mLearningRates.push_back(learningRate);
    mMultipliers.push_back(multiplier);
}


SGDConfig::~SGDConfig()
{

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

    configString << "Lambda(s): ";
    for(double l : mLambdas) {
        configString << l << " ";
    }
    configString << std::endl;
    configString << "Bias multiplier(s): ";
    for(double m : mMultipliers) {
        configString << m << " ";
    }
    configString << std::endl;
    configString << "Bias learning rate(s): ";
    for(double l : mLearningRates) {
        configString << l << " ";
    }
    configString << std::endl;
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
    configString << "Binary classification: ";
    if(binary()) {
        configString << "True" << std::endl;
    } else {
        configString << "False" << std::endl;
    }
    configString << "Probabilistic output: ";
    if(plattScale()) {
        configString << "True" << std::endl;
    } else {
        configString << "False" << std::endl;
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

        mEpsilon = params.get(varName(mEpsilon), 0.0).asDouble();
        mIterations = params.get(varName(mIterations), 0).asUInt64();
        mMaxIterations = params.get(varName(mMaxIterations), 0).asUInt64();
        mBinary = params.get(varName(mBinary), false).asBool();
        mFolds = params.get(varName(mFolds), 5).asInt();
        mPlattScale = params.get(varName(mPlattScale), false).asBool();

        const Json::Value classifiers = params[varName(mClassifierFiles)];
        const Json::Value lambdas = params[varName(mLambdas)];
        const Json::Value learningRates = params[varName(mLearningRates)];
        const Json::Value multipliers = params[varName(mMultipliers)];

        if(classifiers.size()) {
            for(unsigned int idx = 0; idx < classifiers.size(); ++idx) {
                mClassifierFiles.push_back(classifiers[idx].asString());
            }
        } else {
            warning("No classifier file specified, using fallback value.");
            mClassifierFiles.push_back("./trainedClassifier.yml");
        }

        if(lambdas.size()) {
            for(unsigned int idx = 0; idx < lambdas.size(); ++idx) {
                mLambdas.push_back(lambdas[idx].asDouble());
            }
        } else {
            warning("No regularization parameter specified, using fallback value.");
            mLambdas.push_back(0.0001);
        }

        if(learningRates.size()) {
            for(unsigned int idx = 0; idx < learningRates.size(); ++idx) {
                mLearningRates.push_back(learningRates[idx].asDouble());
            }
        } else {
            warning("No bias learning rate parameter specified, using fallback value.");
            mLambdas.push_back(1.0);
        }

        if(multipliers.size()) {
            for(unsigned int idx = 0; idx < multipliers.size(); ++idx) {
                mMultipliers.push_back(multipliers[idx].asDouble());
            }
        } else {
            warning("No biars multiplier parameter specified, using fallback value.");
            mLambdas.push_back(1.0);
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

bool SGDConfig::plattScale() const
{
    return mPlattScale;
}

void SGDConfig::setPlattScale(bool plattScale)
{
    mPlattScale = plattScale;
}

std::vector<double> SGDConfig::lambdas() const
{
    return mLambdas;
}

void SGDConfig::setLambdas(const std::vector<double> &lambdas)
{
    mLambdas = lambdas;
}

std::vector<double> SGDConfig::learningRates() const
{
    return mLearningRates;
}

void SGDConfig::setLearningRates(const std::vector<double> &learningRates)
{
    mLearningRates = learningRates;
}

std::vector<double> SGDConfig::multipliers() const
{
    return mMultipliers;
}

void SGDConfig::setMultipliers(const std::vector<double> &multipliers)
{
    mMultipliers = multipliers;
}


}

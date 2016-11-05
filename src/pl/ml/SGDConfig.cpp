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
                     const int32_t folds,
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


bool SGDConfig::setEpsilon(double epsilon)
{
    mEpsilon = epsilon;
    return setConfigParameter<double>(varName(mEpsilon), epsilon);
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


bool SGDConfig::setIterations(const vl_size &iterations)
{
    mIterations = iterations;
    return setConfigParameter<int32_t>(varName(mIterations), static_cast<int32_t>(iterations));
}


vl_size SGDConfig::maxIterations() const
{
    return mMaxIterations;
}


bool SGDConfig::setMaxIterations(const vl_size &maxIterations)
{
    mMaxIterations = maxIterations;
    return setConfigParameter<int32_t>(varName(mMaxIterations), static_cast<int32_t>(maxIterations));
}


std::vector<std::string> SGDConfig::classifierFiles() const
{
    return mClassifierFiles;
}


bool SGDConfig::setClassifierFiles(const std::vector<std::string> &classifierFiles)
{
    mClassifierFiles = classifierFiles;
    return setConfigParameter<std::string>(varName(mClassifierFiles), classifierFiles);
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

        if(!classifiers.empty()) {
            mClassifierFiles.clear();
            for(uint32_t idx = 0; idx < classifiers.size(); ++idx) {
                mClassifierFiles.push_back(classifiers[idx].asString());
            }
        } else {
            mClassifierFiles.clear();
            warning("No classifier file specified, using fallback value.");
            mClassifierFiles.push_back("./trainedClassifier.yml");
        }

        if(!lambdas.empty()) {
            mLambdas.clear();
            for(uint32_t idx = 0; idx < lambdas.size(); ++idx) {
                mLambdas.push_back(lambdas[idx].asDouble());
            }
        } else {
            mLambdas.clear();
            warning("No regularization parameter specified, using fallback value.");
            mLambdas.push_back(0.0001);
        }

        if(!learningRates.empty()) {
            mLearningRates.clear();
            for(uint32_t idx = 0; idx < learningRates.size(); ++idx) {
                mLearningRates.push_back(learningRates[idx].asDouble());
            }
        } else {
            mLearningRates.clear();
            warning("No bias learning rate parameter specified, using fallback value.");
            mLambdas.push_back(1.0);
        }

        if(!multipliers.empty()) {
            mMultipliers.clear();
            for(uint32_t idx = 0; idx < multipliers.size(); ++idx) {
                mMultipliers.push_back(multipliers[idx].asDouble());
            }
        } else {
            mMultipliers.clear();
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

bool SGDConfig::setBinary(bool binary)
{
    mBinary = binary;
    return setConfigParameter<bool>(varName(mBinary), binary);
}

bool SGDConfig::plattScale() const
{
    return mPlattScale;
}

bool SGDConfig::setPlattScale(bool plattScale)
{
    mPlattScale = plattScale;
    return setConfigParameter<bool>(varName(mPlattScale), plattScale);
}

std::vector<double> SGDConfig::lambdas() const
{
    return mLambdas;
}

bool SGDConfig::setLambdas(const std::vector<double> &lambdas)
{
    mLambdas = lambdas;
    return setConfigParameter<double>(varName(mLambdas), lambdas);
}

std::vector<double> SGDConfig::learningRates() const
{
    return mLearningRates;
}

bool SGDConfig::setLearningRates(const std::vector<double> &learningRates)
{
    mLearningRates = learningRates;
    return setConfigParameter<double>(varName(mLearningRates), learningRates);
}

std::vector<double> SGDConfig::multipliers() const
{
    return mMultipliers;
}

bool SGDConfig::setMultipliers(const std::vector<double> &multipliers)
{
    mMultipliers = multipliers;
    return setConfigParameter<double>(varName(mMultipliers), multipliers);
}


}

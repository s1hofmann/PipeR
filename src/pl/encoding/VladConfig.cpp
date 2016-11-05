#include "VladConfig.h"

namespace pl {


VladConfig::VladConfig(const std::string &identifier,
                       const std::vector<normStrategy> &normalization,
                       const std::vector<std::string> &vocabs,
                       const int32_t clusters,
                       const int32_t iterations,
                       const double epsilon,
                       const int32_t pyramidLevels)
    :
        ConfigContainer(identifier),
        mNormStrategies(normalization),
        mClusters(clusters),
        mVocabs(vocabs),
        mIterations(iterations),
        mEpsilon(epsilon),
        mPyramidLevels(pyramidLevels)
{

}


VladConfig::~VladConfig()
{

}

std::vector<normStrategy> VladConfig::normStrategies() const
{
    return mNormStrategies;
}

bool VladConfig::setNormStrategies(const std::vector<normStrategy> &normStrategies)
{
    mNormStrategies = normStrategies;
    return setConfigParameter<normStrategy>(varName(mNormStrategies), normStrategies);
}

std::vector<std::string> VladConfig::vocabs() const
{
    return mVocabs;
}

bool VladConfig::setVocabs(const std::vector<std::string> &vocabs)
{
    mVocabs = vocabs;
    return setConfigParameter<std::string>(varName(mVocabs), vocabs);
}

std::string VladConfig::path() const
{
    return mPath;
}

bool VladConfig::setPath(const std::string &path)
{
    mPath = path;
    return setConfigParameter<std::string>(varName(mPath), path);
}

int32_t VladConfig::clusters() const
{
    return mClusters;
}

bool VladConfig::setClusters(int32_t clusters)
{
    mClusters = clusters;
    return setConfigParameter<int32_t>(varName(mClusters), clusters);
}

int32_t VladConfig::iterations() const
{
    return mIterations;
}

bool VladConfig::setIterations(int32_t iterations)
{
    mIterations = iterations;
    return setConfigParameter<int32_t>(varName(mIterations), iterations);
}

double VladConfig::epsilon() const
{
    return mEpsilon;
}

bool VladConfig::setEpsilon(double epsilon)
{
    mEpsilon = epsilon;
    return setConfigParameter<double>(varName(mEpsilon), epsilon);
}

int32_t VladConfig::pyramidLevels() const
{
    return mPyramidLevels;
}

bool VladConfig::setPyramidLevels(int32_t pyramidLevels)
{
    mPyramidLevels = pyramidLevels;
    return setConfigParameter<int32_t>(varName(mPyramidLevels), pyramidLevels);
}


std::string VladConfig::toString() const
{
    std::stringstream configString;

    configString << "Normalization: ";
    for(size_t idx = 0; idx < mNormStrategies.size(); ++idx) {
        switch (mNormStrategies[idx]) {
        case normStrategy::NORM_COMPONENT_L2:
            configString << "NORM_COMPONENT_L2";
            break;
        case normStrategy::NORM_GLOBAL_L2:
            configString << "NORM_GLOBAL_L2";
            break;
        case normStrategy::NORM_MASS:
            configString << "NORM_MASS";
            break;
        case normStrategy::NORM_SSR:
            configString << "NORM_SSR";
            break;
        default:
            configString << "Unknown normalization method";
            break;
        }
        if(idx < mNormStrategies.size() - 1) {
            configString << ", ";
        }
    }
    configString << std::endl;

    configString << "No. of clusters: " << mClusters << std::endl;
    configString << "No. of vocabularies: " << mVocabs.size() << std::endl;

    for(size_t idx = 0; idx < mVocabs.size(); ++idx) {
        configString << "Vocab " << idx << ": " << mVocabs[idx] << std::endl;
    }

    configString << "Max. iterations: " << mIterations << std::endl;
    configString << "Epsilon: " << mEpsilon << std::endl;
    configString << "Pyramid levels: " << mPyramidLevels << std::endl;

    return configString.str();
}

bool VladConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mClusters = params.get(varName(mClusters), 64).asInt();
        mIterations = params.get(varName(mIterations), 1000).asInt();
        mPyramidLevels = params.get(varName(mPyramidLevels), 1).asInt();

        const Json::Value vocabs = params[varName(mVocabs)];
        if(vocabs.empty()) {
            mVocabs.clear();
            mVocabs.push_back("./cluster_0.yml");
        } else {
            mVocabs.clear();
            for(int32_t idx = 0; idx < vocabs.size(); ++idx) {
                mVocabs.push_back(vocabs[idx].asString());
            }
        }

        const Json::Value norm = params[varName(mNormStrategies)];

        if(!norm.empty()) {
            mNormStrategies.clear();
            for(int32_t idx = 0; idx < norm.size(); ++idx) {
                std::string strategy = norm[idx].asString();

                if(!strategy.compare(varName(NORM_COMPONENT_L2))) {
                    mNormStrategies.push_back(NORM_COMPONENT_L2);
                } else if(!strategy.compare(varName(NORM_GLOBAL_L2))) {
                    mNormStrategies.push_back(NORM_GLOBAL_L2);
                } else if(!strategy.compare(varName(NORM_MASS))) {
                    mNormStrategies.push_back(NORM_MASS);
                } else if(!strategy.compare(varName(NORM_SSR))) {
                    mNormStrategies.push_back(NORM_SSR);
                } else {
                    warning("Unknown norm strategy, skipping.");
                }
            }
        }

        return true;
    }
}


}

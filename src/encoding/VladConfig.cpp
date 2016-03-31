#include "VladConfig.h"

namespace pl {


VladConfig::VladConfig(const std::string &identifier,
                       const std::vector<normStrategy> &normalization,
                       const std::vector<std::string> &vocabs,
                       const int clusters,
                       const int iterations,
                       const double epsilon,
                       const std::string &path)
    :
        ConfigContainer(identifier),
        mNormStrategies(normalization),
        mClusters(clusters),
        mVocabs(vocabs),
        mIterations(iterations),
        mEpsilon(epsilon),
        mPath(path)
{

}


VladConfig::~VladConfig()
{

}


std::vector<normStrategy> VladConfig::getNormStrategies() const
{
    return this->mNormStrategies;
}


std::string VladConfig::getPath() const
{
    return this->mPath;
}


int VladConfig::getClusters() const
{
    return this->mClusters;
}


int VladConfig::getIterations() const
{
    return this->mIterations;
}

int VladConfig::getVocabCount() const
{
    return this->mVocabs.size();
}

std::vector<std::string> VladConfig::getVocabs() const
{
    return this->mVocabs;
}

double VladConfig::getEpsilon() const
{
    return this->mEpsilon;
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
    configString << "Path: " << mPath << std::endl;

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
        mPath = params.get(varName(mPath), ".").asString();

        const Json::Value vocabs = params[varName(mVocabs)];
        if(vocabs.empty()) {
            mVocabs.push_back("./cluster_0.yml");
        } else {
            for(int idx = 0; idx < vocabs.size(); ++idx) {
                mVocabs.push_back(vocabs[idx].asString());
            }
        }

        const Json::Value norm = params[varName(mNormStrategies)];

        for(int idx = 0; idx < norm.size(); ++idx) {
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

        return true;
    }
}


}

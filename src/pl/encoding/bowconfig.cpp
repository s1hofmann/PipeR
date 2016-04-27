#include "bowconfig.h"

namespace pl {


BOWConfig::BOWConfig(const std::string &identifier,
                       const std::vector<normStrategy> &normalization,
                       const std::vector<std::string> &vocabs,
                       const int clusters,
                       const int iterations,
                       const double epsilon,
                       const int pyramidLevels)
    :
        ConfigContainer(identifier),
        mClusters(clusters),
        mVocabs(vocabs),
        mIterations(iterations),
        mEpsilon(epsilon),
        mPyramidLevels(pyramidLevels)
{

}


BOWConfig::~BOWConfig()
{

}


int BOWConfig::getClusters() const
{
    return this->mClusters;
}


int BOWConfig::getIterations() const
{
    return this->mIterations;
}

int BOWConfig::getVocabCount() const
{
    return this->mVocabs.size();
}

std::vector<std::string> BOWConfig::getVocabs() const
{
    return this->mVocabs;
}

double BOWConfig::getEpsilon() const
{
    return this->mEpsilon;
}

std::string BOWConfig::toString() const
{
    std::stringstream configString;
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

bool BOWConfig::fromJSON(std::string &file)
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
            mVocabs.push_back("./cluster_0.yml");
        } else {
            for(int idx = 0; idx < vocabs.size(); ++idx) {
                mVocabs.push_back(vocabs[idx].asString());
            }
        }

        return true;
    }
}

int BOWConfig::getPyramidLevels() const
{
    return mPyramidLevels;
}

void BOWConfig::setPyramidLevels(int pyramidLevels)
{
    mPyramidLevels = pyramidLevels;
}


}

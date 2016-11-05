#include "bowconfig.h"

namespace pl {


BOWConfig::BOWConfig(const std::string &identifier,
                       const std::vector<normStrategy> &normalization,
                       const std::vector<std::string> &vocabs,
                       const int32_t clusters,
                       const int32_t iterations,
                       const double epsilon,
                       const int32_t pyramidLevels)
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
            mVocabs.clear();
            mVocabs.push_back("./cluster_0.yml");
        } else {
            mVocabs.clear();
            for(int32_t idx = 0; idx < vocabs.size(); ++idx) {
                mVocabs.push_back(vocabs[idx].asString());
            }
        }

        return true;
    }
}

std::vector<std::string> BOWConfig::vocabs() const
{
    return mVocabs;
}

bool BOWConfig::setVocabs(const std::vector<std::string> &vocabs)
{
    mVocabs = vocabs;
    return setConfigParameter<std::string>(varName(mVocabs), vocabs);
}

std::string BOWConfig::path() const
{
    return mPath;
}

bool BOWConfig::setPath(const std::string &path)
{
    mPath = path;
    return setConfigParameter<std::string>(varName(mPath), path);
}

int32_t BOWConfig::clusters() const
{
    return mClusters;
}

bool BOWConfig::setClusters(int32_t clusters)
{
    mClusters = clusters;
    return setConfigParameter<int32_t>(varName(mClusters), clusters);
}

int32_t BOWConfig::iterations() const
{
    return mIterations;
}

bool BOWConfig::setIterations(int32_t iterations)
{
    mIterations = iterations;
    return setConfigParameter<int32_t>(varName(mIterations), iterations);
}

double BOWConfig::epsilon() const
{
    return mEpsilon;
}

bool BOWConfig::setEpsilon(double epsilon)
{
    mEpsilon = epsilon;
    return setConfigParameter<double>(varName(mEpsilon), epsilon);
}

int32_t BOWConfig::pyramidLevels() const
{
    return mPyramidLevels;
}

bool BOWConfig::setPyramidLevels(int32_t pyramidLevels)
{
    mPyramidLevels = pyramidLevels;
    return setConfigParameter<int32_t>(varName(mPyramidLevels), pyramidLevels);
}


}

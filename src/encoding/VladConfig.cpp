#include "VladConfig.h"

namespace pl {


VladConfig::VladConfig(const std::string &identifier,
                       const std::vector<normStrategy> &normalization,
                       const int clusters,
                       const int iterations,
                       const double epsilon,
                       const int vocabs,
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
    configString << "No. of vocabularies: " << mVocabs << std::endl;
    configString << "Max. iterations: " << mIterations << std::endl;
    configString << "Epsilon: " << mEpsilon << std::endl;
    configString << "Path: " << mPath << std::endl;

    return configString.str();
}


}

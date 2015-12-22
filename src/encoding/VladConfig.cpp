#include "VladConfig.h"

namespace pl {


VladConfig::VladConfig(const std::vector<normStrategy> &normalization,
                       const int clusters,
                       const int iterations,
                       const double epsilon,
                       const std::string &path)
    :
        ConfigContainer(),
        mNormStrategies(normalization),
        mClusters(clusters),
        mIterations(iterations),
        mEpsilon(epsilon),
        mPath(path)
{

}


VladConfig::~VladConfig()
{

}


std::vector<normStrategy> VladConfig::getNormStrategies()
{
    return this->mNormStrategies;
}


std::string VladConfig::getPath()
{
    return this->mPath;
}


int VladConfig::getClusters()
{
    return this->mClusters;
}


int VladConfig::getIterations()
{
    return this->mIterations;
}


double VladConfig::getEpsilon()
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
            configString << "Unknown normalization method.";
            break;
        }
        if(idx < mNormStrategies.size() - 1) {
            configString << ", ";
        }
    }
    configString << std::endl;

    configString << "No. of clusters: " << mClusters << std::endl;
    configString << "Max. iterations: " << mIterations << std::endl;
    configString << "Epsilon: " << mEpsilon << std::endl;
    configString << "Path: " << mPath << std::endl;

    return configString.str();
}


}

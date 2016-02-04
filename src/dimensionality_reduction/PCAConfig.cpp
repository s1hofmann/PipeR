#include "PCAConfig.h"


namespace pl {


PCAConfig::PCAConfig(const std::string &identifier,
                     const int components,
                     const double epsilon,
                     const bool whiten,
                     const std::string &path)
    :
        ConfigContainer(identifier),
        mComponents(components),
        mEpsilon(epsilon),
        mWhitening(whiten),
        mPath(path)
{

}


int PCAConfig::getComponents() const
{
    return this->mComponents;
}


double PCAConfig::getEpsilon() const
{
    return this->mEpsilon;
}


bool PCAConfig::getWhitening() const
{
    return this->mWhitening;
}


std::string PCAConfig::getPath() const
{
    return this->mPath;
}


std::string PCAConfig::toString() const
{
    std::stringstream configString;

    configString << "No. of components: " << mComponents << std::endl;
    configString << "Regularization threshold: " << mEpsilon << std::endl;
    configString << "Whitening: " << mWhitening << std::endl;
    configString << "Filename: " << mPath << std::endl;

    return configString.str();
}


}

#include "PCAConfig.h"


namespace pl {


PCAConfig::PCAConfig(const int components,
                     const double epsilon,
                     const bool whiten,
                     const std::string &path)
    :
        ConfigContainer(),
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
    return "I'm not yet implemented!";
}


}

#include "PCAConfig.h"


namespace pipe {


PCAConfig::PCAConfig(int components,
                     double epsilon,
                     bool whiten, const std::__cxx11::string &path)
    :
        ConfigContainer(),
        mComponents(components),
        mEpsilon(epsilon),
        mWhitening(whiten)
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


std::string PCAConfig::toString()
{

}


}

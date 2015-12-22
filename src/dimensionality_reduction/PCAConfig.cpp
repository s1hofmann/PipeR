#include "PCAConfig.h"


namespace pipe {


PCAConfig::PCAConfig(int components,
                     double epsilon,
                     bool whiten = true)
    :
        ConfigContainer(),
        mComponents(components),
        mEpsilon(epsilon),
        mWhitening(whiten)
{

}


int PCAConfig::getComponents()
{
    return this->mComponents;
}

double PCAConfig::getEpsilon()
{
    return this->mEpsilon;
}

bool PCAConfig::getWhitening()
{
    return this->mWhitening;
}


std::string PCAConfig::toString()
{

}


}

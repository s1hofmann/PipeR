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

bool PCAConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mComponents = params.get(varName(mComponents), 64).asInt();
        mEpsilon = params.get(varName(mEpsilon), 0.0001).asDouble();
        mWhitening = params.get(varName(mWhitening), true).asBool();
        mPath = params.get(varName(mPath), ".").asString();

        return true;
    }
}


}

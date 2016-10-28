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

int PCAConfig::components() const
{
    return mComponents;
}

bool PCAConfig::setComponents(int components)
{
    mComponents = components;
    return setConfigParameter<int>(varName(mComponents), components);
}

double PCAConfig::epsilon() const
{
    return mEpsilon;
}

bool PCAConfig::setEpsilon(double epsilon)
{
    mEpsilon = epsilon;
    return setConfigParameter<double>(varName(mEpsilon), epsilon);
}

bool PCAConfig::whitening() const
{
    return mWhitening;
}

bool PCAConfig::setWhitening(bool whitening)
{
    mWhitening = whitening;
    return setConfigParameter<bool>(varName(mWhitening), whitening);
}

std::string PCAConfig::path() const
{
    return mPath;
}

bool PCAConfig::setPath(const std::string &path)
{
    mPath = path;
    return setConfigParameter<std::string>(varName(mPath), path);
}


}

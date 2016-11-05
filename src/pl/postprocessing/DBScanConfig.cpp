#include "DBScanConfig.h"

namespace pl {


DBScanConfig::DBScanConfig(const std::string &identifier)
    :
        ConfigContainer(identifier)
{

}

DBScanConfig::~DBScanConfig()
{

}

int32_t DBScanConfig::minPoints() const
{
    return mMinPoints;
}

bool DBScanConfig::setMinPoints(int32_t minPoints)
{
    mMinPoints = minPoints;
    return setConfigParameter<int32_t>(varName(mMinPoints), minPoints);
}

double DBScanConfig::neighborhoodSize() const
{
    return mNeighborhoodSize;
}

bool DBScanConfig::setNeighborhoodSize(double neighborhoodSize)
{
    mNeighborhoodSize = neighborhoodSize;
    return setConfigParameter<double>(varName(mNeighborhoodSize), neighborhoodSize);
}

std::string DBScanConfig::toString() const
{
    std::stringstream configString;

    configString << "Min. points for cluster: " << minPoints() << std::endl
                 << "Cluster neighborhood: " << neighborhoodSize() << std::endl;

    return configString.str();
}

bool DBScanConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mMinPoints = params.get(varName(mMinPoints), 30).asInt();
        mNeighborhoodSize = params.get(varName(mNeighborhoodSize), 30.0).asDouble();
        return true;
    }
}


}

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

int DBScanConfig::minPoints() const
{
    return mMinPoints;
}

void DBScanConfig::setMinPoints(int minPoints)
{
    mMinPoints = minPoints;
}

double DBScanConfig::neighborhoodSize() const
{
    return mNeighborhoodSize;
}

void DBScanConfig::setNeighborhoodSize(double neighborhoodSize)
{
    mNeighborhoodSize = neighborhoodSize;
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
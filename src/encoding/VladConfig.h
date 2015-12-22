#pragma once

#include "../pipeline/ConfigContainer.h"
#include "../core/encoding/encodingmethod.h"
#include <vector>
#include <sstream>

namespace pl {


class VladConfig : public ConfigContainer
{
public:
    VladConfig(const std::vector<normStrategy> &normalization,
               const int clusters,
               const int iterations = 100,
               const double epsilon = 0.001,
               const std::string &path = "./means.yml");

    virtual ~VladConfig();

    std::vector<normStrategy> getNormStrategies();

    std::string getPath();

    int getClusters();

    int getIterations();

    double getEpsilon();

    virtual std::string toString() const;

private:
    std::vector<normStrategy> mNormStrategies;
    std::string mPath;
    int mClusters;
    int mIterations;
    double mEpsilon;
};


}

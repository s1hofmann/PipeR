#pragma once

#include "../pipeline/ConfigContainer.h"
#include "../core/encoding/encodingmethod.h"
#include <vector>
#include <sstream>

namespace pl {


class VladConfig : public ConfigContainer
{
public:
    VladConfig(const std::string &identifier,
               const std::vector<normStrategy> &normalization,
               const int clusters,
               const int iterations = 100,
               const double epsilon = 0.001,
               const int vocabs = 1,
               const std::string &path = ".");

    virtual ~VladConfig();

    std::vector<normStrategy> getNormStrategies() const;

    std::string getPath() const;

    int getClusters() const;

    int getIterations() const;

    int getVocabCount() const;

    double getEpsilon() const;

    virtual std::string toString() const;

private:
    std::vector<normStrategy> mNormStrategies;
    std::string mPath;
    int mClusters;
    int mIterations;
    int mVocabs;
    double mEpsilon;
};


}

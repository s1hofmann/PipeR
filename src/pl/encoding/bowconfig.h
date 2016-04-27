#pragma once

#include "../pipeline/ConfigContainer.h"
#include "../core/encoding/encodingmethod.h"
#include <vector>
#include <sstream>

namespace pl {


class BOWConfig : public ConfigContainer
{
public:
    BOWConfig(const std::string &identifier,
              const std::vector<normStrategy> &normalization = std::vector<normStrategy>(),
              const std::vector<std::string> &vocabs = std::vector<std::string>(),
              const int clusters = 64,
              const int iterations = 100,
              const double epsilon = 0.001,
              const int pyramidLevels = 1);

    virtual ~BOWConfig();

    std::string getPath() const;

    int getClusters() const;

    int getIterations() const;

    int getVocabCount() const;

    std::vector<std::string> getVocabs() const;

    double getEpsilon() const;

    virtual std::string toString() const;

    // ConfigContainer interface
    virtual bool fromJSON(std::string &file);

    int getPyramidLevels() const;

    void setPyramidLevels(int pyramidLevels);

private:
    std::vector<std::string> mVocabs;
    std::string mPath;
    int mClusters;
    int mIterations;
    double mEpsilon;
    int mPyramidLevels;
};


}

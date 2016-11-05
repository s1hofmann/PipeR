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
              const int32_t clusters = 64,
              const int32_t iterations = 100,
              const double epsilon = 0.001,
              const int32_t pyramidLevels = 1);

    virtual ~BOWConfig();

    virtual std::string toString() const;

    // ConfigContainer interface
    virtual bool fromJSON(std::string &file);

    std::vector<std::string> vocabs() const;
    bool setVocabs(const std::vector<std::string> &vocabs);

    std::string path() const;
    bool setPath(const std::string &path);

    int32_t clusters() const;
    bool setClusters(int32_t clusters);

    int32_t iterations() const;
    bool setIterations(int32_t iterations);

    double epsilon() const;
    bool setEpsilon(double epsilon);

    int32_t pyramidLevels() const;
    bool setPyramidLevels(int32_t pyramidLevels);

private:
    std::vector<std::string> mVocabs;
    std::string mPath;
    int32_t mClusters;
    int32_t mIterations;
    double mEpsilon;
    int32_t mPyramidLevels;
};


}

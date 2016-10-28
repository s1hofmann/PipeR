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
               const std::vector<normStrategy> &normalization = std::vector<normStrategy>(),
               const std::vector<std::string> &vocabs = std::vector<std::string>(),
               const int clusters = 64,
               const int iterations = 100,
               const double epsilon = 0.001,
               const int pyramidLevels = 1);

    virtual ~VladConfig();

    virtual std::string toString() const;

    // ConfigContainer interface
    virtual bool fromJSON(std::string &file);

    bool setPyramidLevels(int pyramidLevels);
    int pyramidLevels() const;
    bool setEpsilon(double epsilon);
    double epsilon() const;
    bool setIterations(int iterations);
    int iterations() const;
    bool setClusters(int clusters);
    int clusters() const;
    bool setPath(const std::string &path);
    std::string path() const;
    bool setVocabs(const std::vector<std::string> &vocabs);
    std::vector<std::string> vocabs() const;
    bool setNormStrategies(const std::vector<normStrategy> &normStrategies);
    std::vector<normStrategy> normStrategies() const;
private:
    std::vector<normStrategy> mNormStrategies;
    std::vector<std::string> mVocabs;
    std::string mPath;
    int mClusters;
    int mIterations;
    double mEpsilon;
    int mPyramidLevels;
};


}

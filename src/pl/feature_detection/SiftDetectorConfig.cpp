//
// Created by Simon Hofmann on 19.11.15.
//

#include <sstream>
#include "SiftDetectorConfig.h"

namespace pl {


SiftDetectorConfig::SiftDetectorConfig(const std::string &identifier,
                                       int32_t nBestFeatures,
                                       int32_t nOctaveLayers,
                                       double contrastThreshold,
                                       double edgeThreshold,
                                       double sigma,
                                       bool augment)
    :
        ConfigContainer(identifier,
                        "Parameter description",
                        "Help text"),
        mBestFeatures(nBestFeatures),
        mOctaves(nOctaveLayers),
        mContrastThresh(contrastThreshold),
        mEdgeThresh(edgeThreshold),
        mSigma(sigma)
{
}


SiftDetectorConfig::~SiftDetectorConfig()
{

}


std::string SiftDetectorConfig::toString() const
{
    std::stringstream configString;

    configString << "Best features: " << bestFeatures() << std::endl
                 << "Octaves: " << octaves() << std::endl
                 << "Contrast threshold: " << contrastThresh() << std::endl
                 << "Edge threshold: " << edgeThresh() << std::endl
                 << "Sigma: " << sigma() << std::endl;

    return configString.str();
}

bool SiftDetectorConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mBestFeatures = params.get(varName(mBestFeatures), 0).asInt();
        mOctaves = params.get(varName(mOctaves), 3).asInt();
        mContrastThresh = params.get(varName(mContrastThresh), 0.04).asDouble();
        mEdgeThresh = params.get(varName(mEdgeThresh), 10.0).asDouble();
        mSigma = params.get(varName(mSigma), 1.6).asDouble();

        return true;
    }
}

int32_t SiftDetectorConfig::bestFeatures() const
{
    return mBestFeatures;
}

bool SiftDetectorConfig::setBestFeatures(int32_t bestFeatures)
{
    mBestFeatures = bestFeatures;
    return setConfigParameter<int32_t>(varName(mBestFeatures), bestFeatures);
}

int32_t SiftDetectorConfig::octaves() const
{
    return mOctaves;
}

bool SiftDetectorConfig::setOctaves(int32_t octaves)
{
    mOctaves = octaves;
    return setConfigParameter<int32_t>(varName(mOctaves), octaves);
}

double SiftDetectorConfig::contrastThresh() const
{
    return mContrastThresh;
}

bool SiftDetectorConfig::setContrastThresh(double contrastThresh)
{
    mContrastThresh = contrastThresh;
    return setConfigParameter<double>(varName(mContrastThresh), contrastThresh);
}

double SiftDetectorConfig::edgeThresh() const
{
    return mEdgeThresh;
}

bool SiftDetectorConfig::setEdgeThresh(double edgeThresh)
{
    mEdgeThresh = edgeThresh;
    return setConfigParameter<double>(varName(mEdgeThresh), edgeThresh);
}

double SiftDetectorConfig::sigma() const
{
    return mSigma;
}

bool SiftDetectorConfig::setSigma(double sigma)
{
    mSigma = sigma;
    return setConfigParameter<double>(varName(mSigma), sigma);
}


}

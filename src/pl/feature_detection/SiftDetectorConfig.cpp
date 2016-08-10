//
// Created by Simon Hofmann on 19.11.15.
//

#include <sstream>
#include "SiftDetectorConfig.h"

namespace pl {


SiftDetectorConfig::SiftDetectorConfig(const std::string &identifier,
                                       int nBestFeatures,
                                       int nOctaveLayers,
                                       double contrastThreshold,
                                       double edgeThreshold,
                                       double sigma)
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

    configString << "Best features: " << getBestFeatures() << std::endl
                 << "Octaves: " << getOctaves() << std::endl
                 << "Contrast threshold: " << getContrastThresh() << std::endl
                 << "Edge threshold: " << getEdgeThresh() << std::endl
                 << "Sigma: " << getSigma() << std::endl;

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


}

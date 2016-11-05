//
// Created by Simon Hofmann on 19.11.15.
//

#include <sstream>
#include "SiftExtractorConfig.h"

namespace pl {


SiftExtractorConfig::SiftExtractorConfig(const std::string &identifier,
                                         int32_t nBestFeatures,
                                         int32_t nOctaveLayers,
                                         double contrastThreshold,
                                         double edgeThreshold,
                                         double sigma,
                                         bool augment)
    :
        FeatureConfig(identifier,
                      augment),
        mBestFeatures(nBestFeatures),
        mOctaves(nOctaveLayers),
        mContrastThresh(contrastThreshold),
        mEdgeThresh(edgeThreshold),
        mSigma(sigma)
{
}


SiftExtractorConfig::~SiftExtractorConfig()
{

}


std::string SiftExtractorConfig::toString() const
{
    std::stringstream configString;

    configString << "Best features: " << bestFeatures() << std::endl
                 << "Octaves: " << octaves() << std::endl
                 << "Contrast threshold: " << contrastThresh() << std::endl
                 << "Edge threshold: " << edgeThresh() << std::endl
                 << "Sigma: " << sigma() << std::endl
                 << "Augment: ";
    if(mAugment == true) {
        configString << "true" << std::endl;
    } else {
        configString << "false" << std::endl;
    }

    return configString.str();
}

bool SiftExtractorConfig::fromJSON(std::string &file)
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
        mAugment = params.get(varName(mAugment), true).asBool();

        return true;
    }
}

int32_t SiftExtractorConfig::bestFeatures() const
{
    return mBestFeatures;
}

bool SiftExtractorConfig::setBestFeatures(int32_t bestFeatures)
{
    mBestFeatures = bestFeatures;
    return setConfigParameter<int32_t>(varName(mBestFeatures), bestFeatures);
}

int32_t SiftExtractorConfig::octaves() const
{
    return mOctaves;
}

bool SiftExtractorConfig::setOctaves(int32_t octaves)
{
    mOctaves = octaves;
    return setConfigParameter<int32_t>(varName(mOctaves), octaves);
}

double SiftExtractorConfig::contrastThresh() const
{
    return mContrastThresh;
}

bool SiftExtractorConfig::setContrastThresh(double contrastThresh)
{
    mContrastThresh = contrastThresh;
    return setConfigParameter<double>(varName(mContrastThresh), contrastThresh);
}

double SiftExtractorConfig::edgeThresh() const
{
    return mEdgeThresh;
}

bool SiftExtractorConfig::setEdgeThresh(double edgeThresh)
{
    mEdgeThresh = edgeThresh;
    return setConfigParameter<double>(varName(mEdgeThresh), edgeThresh);
}

double SiftExtractorConfig::sigma() const
{
    return mSigma;
}

bool SiftExtractorConfig::setSigma(double sigma)
{
    mSigma = sigma;
    return setConfigParameter<double>(varName(mSigma), sigma);
}


}

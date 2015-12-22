//
// Created by Simon Hofmann on 19.11.15.
//

#include <sstream>
#include "SiftConfigContainer.h"

namespace pl {


SiftConfigContainer::SiftConfigContainer(int nBestFeatures,
                                         int nOctaveLayers,
                                         double contrastThreshold,
                                         double edgeThreshold,
                                         double sigma)
    :
        ConfigContainer("Parameter description", "Help text"),
        mBestFeatures(nBestFeatures),
        mOctaves(nOctaveLayers),
        mContrastThresh(contrastThreshold),
        mEdgeThresh(edgeThreshold),
        mSigma(sigma)
{
}


SiftConfigContainer::~SiftConfigContainer()
{

}


std::string SiftConfigContainer::toString() const
{
    std::stringstream configString;

    configString << "Best features: " << getBestFeatures() << std::endl
                 << "Octaves: " << getOctaves() << std::endl
                 << "Contrast threshold: " << getContrastThresh() << std::endl
                 << "Edge threshold: " << getEdgeThresh() << std::endl
                 << "Sigma: " << getSigma() << std::endl;

    return configString.str();
}


}

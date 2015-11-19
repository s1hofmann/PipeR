//
// Created by Simon Hofmann on 19.11.15.
//

#include "SiftConfigContainer.h"

namespace pipe {


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


int SiftConfigContainer::bestFeatures() const
{
    return mBestFeatures;
}


int SiftConfigContainer::octaves() const
{
    return mOctaves;
}


double SiftConfigContainer::contrastThresh() const
{
    return mContrastThresh;
}


double SiftConfigContainer::edgeThresh() const
{
    return mEdgeThresh;
}


double SiftConfigContainer::sigma() const
{
    return mSigma;
}


}

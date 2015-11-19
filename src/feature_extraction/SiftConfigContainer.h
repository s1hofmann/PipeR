//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pipe {


class SiftConfigContainer : public ConfigContainer {
public:
    SiftConfigContainer(int nBestFeatures = 0,
                        int nOctaveLayers = 3,
                        double contrastThreshold = 0.04,
                        double edgeThreshold = 10,
                        double sigma = 1.6);

    virtual ~SiftConfigContainer();

    int bestFeatures() const;

    int octaves() const;

    double contrastThresh() const;

    double edgeThresh() const;

    double sigma() const;

    virtual std::string toString() const;

private:
    int mBestFeatures;
    int mOctaves;
    double mContrastThresh;
    double mEdgeThresh;
    double mSigma;
};


}

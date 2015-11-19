//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pipe {

class VesselMaskConfig : public ConfigContainer {
public:
    VesselMaskConfig(int octaves = 3,
                     int stages = 3,
                     double sigma = 1,
                     double beta = 0.5,
                     double c = 15);

    inline int getOctaves() const {
        return mOctaves;
    }

    inline int getStages() const {
        return mStages;
    }

    inline double getSigma() const {
        return mSigma;
    }

    inline double getBeta() const {
        return mBeta;
    }

    inline double getC() const {
        return mC;
    }

    virtual ~VesselMaskConfig();

    virtual std::string toString() const;

private:
    int mOctaves;
    int mStages;
    double mSigma;
    double mBeta;
    double mC;
};


}

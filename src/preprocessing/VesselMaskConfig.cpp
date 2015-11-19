//
// Created by Simon Hofmann on 19.11.15.
//

#include <sstream>
#include "VesselMaskConfig.h"

namespace pipe {


VesselMaskConfig::VesselMaskConfig(int octaves,
                                   int stages,
                                   double sigma,
                                   double beta,
                                   double c)
    :
        mOctaves(octaves),
        mStages(stages),
        mSigma(sigma),
        mBeta(beta),
        mC(c)
{

}


std::string VesselMaskConfig::toString() const
{
    std::stringstream vesselConfig;

    vesselConfig << "Octaves: " << getOctaves() << std::endl
                 << "Stages: " << getStages() << std::endl
                 << "Sigma: " << getSigma() << std::endl
                 << "Beta: " << getBeta() << std::endl
                 << "C: " << getC() << std::endl;

    return vesselConfig.str();
}


VesselMaskConfig::~VesselMaskConfig()
{

}


}

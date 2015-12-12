//
// Created by Simon Hofmann on 12.12.15.
//

#include "VesselMask.h"
#include "../core/vesselfilter.h"

namespace pipe {


VesselMask::VesselMask(const int octaves,
                       const int stages,
                       const double sigma,
                       const double beta,
                       const double c)
    :
        mOctaves(octaves),
        mStages(stages),
        mSigma(sigma),
        mBeta(beta),
        mC(c)
{

}


VesselMask::~VesselMask() {

}


cv::Mat VesselMask::create(const cv::Mat &input)
{
    VesselFilter vesselFilter(mSigma,
                              mOctaves,
                              mStages);

    return vesselFilter.compute(input, mBeta, mC);
}


std::string VesselMask::toString() {
    std::stringstream s;

    s << "Mask: " << mName << std::endl
      << "Parameters: " << std::endl
      << "Sigma: " << mSigma << std::endl
      << "Octaves: " << mOctaves << std::endl
      << "Stages: " << mStages << std::endl
      << std::endl
      << "Beta: " << mBeta << std::endl
      << "C: " << mC << std::endl;

    return s.str();
}


}

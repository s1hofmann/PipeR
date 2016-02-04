//
// Created by Simon Hofmann on 12.12.15.
//

#include "VesselMask.h"

namespace pl {


VesselMask::VesselMask(const int octaves,
                       const int stages,
                       const double sigma,
                       const double beta,
                       const double c,
                       const std::string &name)
    :
        MaskGenerator(name),
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

    cv::Mat result = vesselFilter.compute(input, mBeta, mC);
    cv::Mat1b mask = cv::Mat1b::zeros(input.size());
    mask.setTo(1, result > 0.5);

    return mask;
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


std::string VesselMask::name()
{
    return this->mName;
}


}

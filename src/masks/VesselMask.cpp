//
// Created by Simon Hofmann on 12.12.15.
//

#include "VesselMask.h"

namespace pl {


VesselMask::VesselMask(const std::string &identifier,
                       const int octaves,
                       const int stages,
                       const double sigma,
                       const double beta,
                       const double c)
    :
        MaskGenerator(identifier),
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

    s << "Mask: " << mIdentifier << std::endl
      << "Parameters: " << std::endl
      << "Sigma: " << mSigma << std::endl
      << "Octaves: " << mOctaves << std::endl
      << "Stages: " << mStages << std::endl
      << std::endl
      << "Beta: " << mBeta << std::endl
      << "C: " << mC << std::endl;

    return s.str();
}

bool VesselMask::fromJSON(const std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mOctaves = params.get(varName(mOctaves), 3).asInt();
        mStages = params.get(varName(mStages), 3).asInt();

        mSigma = params.get(varName(mSigma), 1).asDouble();
        mBeta = params.get(varName(mBeta), 0.5).asDouble();
        mC = params.get(varName(mC), 12).asDouble();

        return true;
    }
}


std::string VesselMask::identifier()
{
    return this->mIdentifier;
}


}

//
// Created by Simon Hofmann on 12.12.15.
//


#pragma once

#include "MaskGenerator.h"

namespace pipe {


class VesselMask : public MaskGenerator {
public:
    VesselMask(const int octaves,
               const int stages,
               const double sigma,
               const double beta,
               const double c);

    ~VesselMask();

    cv::Mat create(const cv::Mat &input);

    std::string toString();

private:
    int mOctaves;
    int mStages;

    double mSigma;
    double mBeta;
    double mC;
};


}


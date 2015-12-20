//
// Created by Simon Hofmann on 12.12.15.
//


#pragma once

#include "MaskGenerator.h"

namespace pipe {


class VesselMask : public MaskGenerator {
public:
    VesselMask(const int octaves = 3,
               const int stages = 3,
               const double sigma = 1.5,
               const double beta = 0.5,
               const double c = 15,
               const std::string &name = "Vessel mask generator");

    ~VesselMask();

    cv::Mat create(const cv::Mat &input);

    std::string toString();

    std::string name();

private:
    int mOctaves;
    int mStages;

    double mSigma;
    double mBeta;
    double mC;
};


}


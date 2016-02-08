//
// Created by Simon Hofmann on 12.12.15.
//


#pragma once

#include "MaskGenerator.h"
#include "../core/masks/vesselfilter.h"

namespace pl {


class VesselMask : public MaskGenerator {
public:
    VesselMask();

    VesselMask(const std::string &identifier = "vessel",
               const int octaves = 3,
               const int stages = 3,
               const double sigma = 1,
               const double beta = 0.5,
               const double c = 15);

    ~VesselMask();

    cv::Mat create(const cv::Mat &input);

    std::string toString();

    virtual bool fromJSON(const std::string &file);

    std::string identifier();

private:
    int mOctaves;
    int mStages;

    double mSigma;
    double mBeta;
    double mC;
};


}


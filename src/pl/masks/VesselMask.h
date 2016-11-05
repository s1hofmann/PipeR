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
               const int32_t octaves = 3,
               const int32_t stages = 3,
               const double sigma = 1,
               const double beta = 0.5,
               const double c = 15,
               const double threshold = 0.5);

    ~VesselMask();

    cv::Mat create(const cv::Mat &input);

    std::string toString() const;

    virtual bool fromJSON(const std::string &file);

    std::string identifier() const;

private:
    int32_t mOctaves;
    int32_t mStages;

    double mSigma;
    double mBeta;
    double mC;
    double mThreshold;
};


}


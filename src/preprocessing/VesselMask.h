//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "PreprocessingStep.h"

namespace pipe {


class VesselMask : public MaskGenerationStep {
public:
    VesselMask(const cv::Ptr<ConfigContainer> &config,
               const std::string &info = "Vesselness mask generation");

    virtual ~VesselMask();
};


}

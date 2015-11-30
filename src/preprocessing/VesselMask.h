//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "PreprocessingStep.h"
#include "VesselMaskConfig.h"
#include "../core/vesselfilter.h"

namespace pipe {


class VesselMask : public MaskGenerationStep {
public:
    VesselMask(const cv::Ptr<ConfigContainer> &config,
               const std::string &info = "Vesselness mask generation");

    virtual ~VesselMask();

    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &mask) const;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &mask) const;

private:
};


}

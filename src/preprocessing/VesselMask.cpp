//
// Created by Simon Hofmann on 19.11.15.
//

#include <typeinfo>
#include <iostream>
#include "VesselMask.h"
#include "../pipeline/return_codes.h"


namespace pipe {


VesselMask::VesselMask(const cv::Ptr<ConfigContainer> &config,
                       const std::string &info)
    :
        MaskGenerationStep(config, info)
{

}


VesselMask::~VesselMask() {

}


cv::Mat VesselMask::train(const cv::Mat &input, const cv::Mat &mask) const {
    cv::Mat result;

    cv::Ptr<VesselMaskConfig> maskConfig;
    maskConfig = this->mConfig.dynamicCast<VesselMaskConfig>();
    VesselFilter vesselFilter(maskConfig->getSigma(),
                              maskConfig->getOctaves(),
                              maskConfig->getStages());

    try {
        result = vesselFilter.compute(input,
                                      maskConfig->getBeta(),
                                      maskConfig->getC(),
                                      mask);
    } catch (cv::Exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    return result;
}


cv::Mat VesselMask::run(const cv::Mat &input, const cv::Mat &mask) const {
    return this->train(input, mask);
}
}

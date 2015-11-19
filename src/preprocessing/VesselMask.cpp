//
// Created by Simon Hofmann on 19.11.15.
//

#include "VesselMask.h"


namespace pipe {


VesselMask::VesselMask(const cv::Ptr<ConfigContainer> &config,
                       const std::string &info)
    :
        MaskGenerationStep(config, info)
{

}


VesselMask::~VesselMask() {

}


}

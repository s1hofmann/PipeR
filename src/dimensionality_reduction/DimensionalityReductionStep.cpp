//
// Created by Simon Hofmann on 16.11.15.
//

#include "DimensionalityReductionStep.h"

namespace pipe {

DimensionalityReductionStep::DimensionalityReductionStep(const cv::Ptr<ConfigContainer> config,
                                                         const std::string &info)
    :
        PipelineStep(config,
                     info)
{

}

DimensionalityReductionStep::~DimensionalityReductionStep()
{

}


}

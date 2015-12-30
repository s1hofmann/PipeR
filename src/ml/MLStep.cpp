//
// Created by Simon Hofmann on 28.12.15.
//

#include "MLStep.h"

namespace pl {

MLStep::MLStep(const cv::Ptr<ConfigContainer> config,
               const std::string &info)
    :
        PipelineStep(config,
                     info)
{

}

MLStep::~MLStep()
{

}


}

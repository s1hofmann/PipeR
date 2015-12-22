//
// Created by Simon Hofmann on 16.11.15.
//

#include "EncodingStep.h"

namespace pl {


EncodingStep::EncodingStep(const cv::Ptr<ConfigContainer> config,
                           const std::string &info)
    :
        PipelineStep(config,
                     info)
{

}


EncodingStep::~EncodingStep()
{

}


}

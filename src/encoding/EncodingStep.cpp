//
// Created by Simon Hofmann on 16.11.15.
//

#include "EncodingStep.h"

namespace pipe {


EncodingStep::EncodingStep(const std::string &info,
                           const std::string &usage,
                           const std::string &help)
        :
        PipelineStep(info, usage, help)
{

}


EncodingStep::~EncodingStep()
{

}


}
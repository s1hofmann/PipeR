//
// Created by Simon Hofmann on 16.11.15.
//

#include "PreprocessingStep.h"

namespace pipe {


PreprocessingStep::PreprocessingStep(const std::string &info,
                                     const std::string &usage,
                                     const std::string &help)
    :
        PipelineStep(info, usage, help)
{

}


    PreprocessingStep::~PreprocessingStep() {

    }
}

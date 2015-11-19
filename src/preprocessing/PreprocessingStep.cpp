//
// Created by Simon Hofmann on 16.11.15.
//

#include "PreprocessingStep.h"

namespace pipe {


PreprocessingStep::PreprocessingStep(const cv::Ptr<ConfigContainer> config,
                                     const std::string &info)
    :
        PipelineStep(config,
                     info)
{

}


PreprocessingStep::~PreprocessingStep()
{

}


}

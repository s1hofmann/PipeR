//
// Created by Simon Hofmann on 16.11.15.
//

#include "FeatureExtractionStep.h"

namespace pipe {


FeatureExtractionStep::FeatureExtractionStep(const std::string &info,
                                             const std::string &usage,
                                             const std::string &help)
    :
        PipelineStep(info, usage, help)
{

}


FeatureExtractionStep::~FeatureExtractionStep() {

}


}

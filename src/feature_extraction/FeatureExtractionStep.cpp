//
// Created by Simon Hofmann on 16.11.15.
//

#include "FeatureExtractionStep.h"

namespace pipe {


FeatureExtractionStep::FeatureExtractionStep(const cv::Ptr<ConfigContainer> config,
                                             const std::string &info)
    :
        PipelineStep(config,
                     info)
{

}


FeatureExtractionStep::~FeatureExtractionStep() {

}


}

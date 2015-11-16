//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <string>
#include "../pipeline/PipelineStep.h"


namespace pipe {


class FeatureExtractionStep : public PipelineStep {
public:
    FeatureExtractionStep();
    virtual ~FeatureExtractionStep() = 0;

    virtual int execute() = 0;

private:
    std::string usage;
    std::string helpText;

    std::string name;
};


}


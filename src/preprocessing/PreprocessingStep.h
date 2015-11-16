//
// Created by Simon Hofmann on 16.11.15.
//

#pragma once

#include <string>

#include "../pipeline/PipelineStep.h"

namespace pipe {


class PreprocessingStep : public PipelineStep {
public:
    PreprocessingStep();

    virtual ~PreprocessingStep() = 0;

    virtual int execute() = 0;

private:
};


}

//
// Created by Simon Hofmann on 16.11.15.
//

#pragma once

#include <string>

#include "../pipeline/PipelineStep.h"

namespace pipe {


class PreprocessingStep : public PipelineStep {
public:
    PreprocessingStep(const std::string &info = std::string(),
                      const std::string &usage = std::string(),
                      const std::string &help = std::string());

    virtual ~PreprocessingStep();

    virtual int execute() = 0;

private:
};


}

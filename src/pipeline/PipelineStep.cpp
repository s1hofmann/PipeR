//
// Created by Simon Hofmann on 16.11.15.
//

#include "PipelineStep.h"

namespace pipe {


PipelineStep::PipelineStep(const std::string &info,
                           const std::string &usage,
                           const std::string &help)
{
    this->name = info;
    this->usageText = usage;
    this->helpText = help;
}


PipelineStep::~PipelineStep()
{

}


std::string PipelineStep::help()
{
    return this->helpText;
}


std::string PipelineStep::usage()
{
    return this->usageText;
}


std::string PipelineStep::info()
{
    return this->name;
}


}

//
// Created by Simon Hofmann on 16.11.15.
//

#include "PipelineStep.h"

namespace pl {


PipelineStep::PipelineStep(const cv::Ptr<ConfigContainer> config)
    :
        mConfig(config)
{

}


PipelineStep::~PipelineStep()
{

}


std::string PipelineStep::help()
{
    return mConfig->help();
}


std::string PipelineStep::usage()
{
    return mConfig->usage();
}


std::string PipelineStep::info()
{
    return mConfig->identifier();
}


std::string PipelineStep::config() const {
    return mConfig->toString();
}

std::string PipelineStep::identifier() const
{
    return mConfig->identifier();
}

std::string PseudoPipelineStep::info()
{
    return mConfig->identifier();
}

std::string PseudoPipelineStep::help()
{
    return mConfig->help();
}

std::string PseudoPipelineStep::usage()
{
    return mConfig->usage();
}

std::string PseudoPipelineStep::config() const
{
    return mConfig->toString();
}

PseudoPipelineStep::PseudoPipelineStep(const cv::Ptr<ConfigContainer> config)
    :
        mConfig(config)
{

}

PseudoPipelineStep::~PseudoPipelineStep()
{

}


}

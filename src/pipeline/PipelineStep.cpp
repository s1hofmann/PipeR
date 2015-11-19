//
// Created by Simon Hofmann on 16.11.15.
//

#include "PipelineStep.h"

namespace pipe {


PipelineStep::PipelineStep(const cv::Ptr<ConfigContainer> config,
                           const std::string &info)
    :
        mName(info),
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
    return mName;
}


std::string PipelineStep::config() const {
    std::stringstream config;

    config << mName << " config:" << std::endl << mConfig->toString();
    return config.str();
}


}

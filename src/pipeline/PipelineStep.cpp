//
// Created by Simon Hofmann on 16.11.15.
//

#include "PipelineStep.h"

namespace pl {


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


void PipelineStep::log(const std::string &text) const
{
    std::stringstream s;

    s << "LOG: " << this->mName << ": " << text;

    std::cout << s.str() << std::endl;
}


void PipelineStep::warning(const std::__cxx11::string &text) const
{
    std::stringstream s;

    s << "WARNING: " << this->mName << ": " << text;

    std::cout << s.str() << std::endl;
}


void PipelineStep::debug(const std::__cxx11::string &text) const
{
    std::stringstream s;

    s << "DEBUG: " << this->mName << ": " << text;

    std::cout << s.str() << std::endl;
}


}

#include "PipelineConfig.h"

namespace pl {


PipelineConfig::PipelineConfig(const std::string &identifier)
    :
        ConfigContainer(identifier)
{
}


PipelineConfig::~PipelineConfig()
{

}


std::string PipelineConfig::descriptorDir() const
{
    return mDescriptorDir;
}


void PipelineConfig::setDescriptorDir(const std::string &descriptorDir)
{
    mDescriptorDir = descriptorDir;
}


std::string PipelineConfig::descriptorLabelFile() const
{
    return mDescriptorLabelFile;
}


void PipelineConfig::setDescriptorLabelFile(const std::string &descriptorLabelFile)
{
    mDescriptorLabelFile = descriptorLabelFile;
}


std::string PipelineConfig::toString() const
{
    return std::string();
}


}

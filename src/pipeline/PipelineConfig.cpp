#include "PipelineConfig.h"

namespace pl {


PipelineConfig::PipelineConfig()
    :
        mDimensionalityReductionSubset(150000)
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


std::string PipelineConfig::dimensionalityReductionPath() const
{
    return mDimensionalityReductionPath;
}


void PipelineConfig::setDimensionalityReductionPath(const std::string &dimensionalityReductionPath)
{
    mDimensionalityReductionPath = dimensionalityReductionPath;
}


int PipelineConfig::dimensionalityReductionSubset() const
{
    return mDimensionalityReductionSubset;
}


void PipelineConfig::setDimensionalityReductionSubset(int dimensionalityReductionSubset)
{
    mDimensionalityReductionSubset = dimensionalityReductionSubset;
}


std::string PipelineConfig::toString() const
{
    return std::string();
}


}

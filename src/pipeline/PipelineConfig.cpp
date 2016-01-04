#include "PipelineConfig.h"

namespace pl {


PipelineConfig::PipelineConfig()
{

}

PipelineConfig::~PipelineConfig()
{

}

std::string PipelineConfig::pca() const
{
    return mPca;
}

void PipelineConfig::setPca(const std::string &pca)
{
    mPca = pca;
}

std::vector<std::string> PipelineConfig::vocabs() const
{
    return mVocabs;
}

void PipelineConfig::setVocabs(const std::vector<std::string> &vocabs)
{
    mVocabs = vocabs;
}

std::string PipelineConfig::descriptorLabelFile() const
{
    return mDescriptorLabelFile;
}

void PipelineConfig::setDescriptorLabelFile(const std::string &descriptorLabelFile)
{
    mDescriptorLabelFile = descriptorLabelFile;
}

std::string PipelineConfig::descriptorDir() const
{
    return mDescriptorDir;
}

void PipelineConfig::setDescriptorDir(const std::string &descriptorDir)
{
    mDescriptorDir = descriptorDir;
}


}

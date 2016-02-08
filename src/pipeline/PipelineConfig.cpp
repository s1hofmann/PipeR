#include "PipelineConfig.h"

namespace pl {


PipelineConfig::PipelineConfig(const std::string &identifier)
    :
        ConfigContainer(identifier)
{
}

PipelineConfig::PipelineConfig(const std::string &identifier,
                               const std::string &descriptorDir,
                               const std::string &descriptorLabelFile)
    :
        ConfigContainer(identifier),
        mDescriptorDir(descriptorDir),
        mDescriptorLabelFile(descriptorLabelFile)
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

bool PipelineConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mDescriptorDir = params[varName(mDescriptorDir)].asString();
        mDescriptorLabelFile = params[varName(mDescriptorLabelFile)].asString();
        const Json::Value vocabs = params[varName(mVocabs)];
        for(int idx = 0; idx < vocabs.size(); ++idx) {
            mVocabs.push_back(vocabs[idx].asString());
        }

        return true;
    }
}


std::string PipelineConfig::toString() const
{
    return std::string();
}


}

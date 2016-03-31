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

        mDescriptorDir = params.get(varName(mDescriptorDir), ".").asString();
        mDescriptorLabelFile = params.get(varName(mDescriptorLabelFile), "./descriptorlabels.dat").asString();
        mMaxDescriptors = params.get(varName(mMaxDescriptors), 150000).asInt();
        mRebuildClusters = params.get(varName(mRebuildClusters), true).asBool();
        mRebuildPca = params.get(varName(mRebuildPca), true).asBool();
        mRebuildDescriptors = params.get(varName(mRebuildDescriptors), true).asBool();
        std::string modeString = params.get(varName(mPipelineMode), "MODE_TRAIN").asString();
        mPipelineMode = str2mode(modeString);
        mDebugMode = params.get(varName(mDebugMode), false).asBool();

        return true;
    }
}

int PipelineConfig::maxDescriptors() const
{
    return mMaxDescriptors;
}

void PipelineConfig::setMaxDescriptors(int value)
{
    mMaxDescriptors = value;
}

bool PipelineConfig::rebuildPca() const
{
    return mRebuildPca;
}

void PipelineConfig::setRebuildPca(bool rebuildPca)
{
    mRebuildPca = rebuildPca;
}

bool PipelineConfig::rebuildClusters() const
{
    return mRebuildClusters;
}

void PipelineConfig::setRebuildClusters(bool rebuildClusters)
{
    mRebuildClusters = rebuildClusters;
}

bool PipelineConfig::rebuildDescriptors() const
{
    return mRebuildDescriptors;
}

void PipelineConfig::setRebuildDescriptors(bool rebuildDescriptors)
{
    mRebuildDescriptors = rebuildDescriptors;
}

PipeLineMode PipelineConfig::pipelineMode() const
{
    return mPipelineMode;
}

void PipelineConfig::setPipelineMode(const PipeLineMode &pipelineMode)
{
    mPipelineMode = pipelineMode;
}

bool PipelineConfig::debugMode() const
{
    return mDebugMode;
}

void PipelineConfig::setDebugMode(bool debugMode)
{
    mDebugMode = debugMode;
}

PipeLineMode PipelineConfig::str2mode(const std::__cxx11::string &modeString)
{
    if(modeString.compare("MODE_TRAIN") == 0) {
        return PipeLineMode::MODE_TRAIN;
    } else if(modeString.compare("MODE_RUN") == 0) {
        return PipeLineMode::MODE_RUN;
    } else if(modeString.compare("MODE_OPTIMIZE") == 0) {
        return PipeLineMode::MODE_OPTIMIZE;
    } else {
        return PipeLineMode::MODE_TRAIN;
    }
}

std::string PipelineConfig::toString() const
{
    std::stringstream configString;

    configString << "Debug: " << (mDebugMode ? "true" : "false") << std::endl;
    configString << "Mode: ";
    if(mPipelineMode == PipeLineMode::MODE_TRAIN) {
        configString << "MODE_TRAIN" << std::endl;
    } else if(mPipelineMode == PipeLineMode::MODE_RUN) {
        configString << "MODE_RUN" << std::endl;
    } else if(mPipelineMode == PipeLineMode::MODE_OPTIMIZE) {
        configString << "MODE_OPTIMIZE" << std::endl;
    }

    std::cout << std::endl;

    configString << "Descriptor directory: " << mDescriptorDir << std::endl;
    configString << "Descriptor labelfile: " << mDescriptorLabelFile << std::endl;

    std::cout << std::endl;

    configString << "Rebuild descriptors: " << (mRebuildDescriptors ? "true" : "false") << std::endl;
    configString << "Rebuild clusters: " << (mRebuildClusters ? "true" : "false") << std::endl;
    configString << "Rebuild PCA: " << (mRebuildPca ? "true" : "false") << std::endl;

    return configString.str();
}


}

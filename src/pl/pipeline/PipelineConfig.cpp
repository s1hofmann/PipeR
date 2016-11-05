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


bool PipelineConfig::setDescriptorDir(const std::string &descriptorDir)
{
    mDescriptorDir = descriptorDir;
    return setConfigParameter<std::string>(varName(mDescriptorDir), descriptorDir);
}


std::string PipelineConfig::descriptorLabelFile() const
{
    return mDescriptorLabelFile;
}


bool PipelineConfig::setDescriptorLabelFile(const std::string &descriptorLabelFile)
{
    mDescriptorLabelFile = descriptorLabelFile;
    return setConfigParameter<std::string>(varName(mDescriptorLabelFile), descriptorLabelFile);
}

bool PipelineConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        mDescriptorDir = params.get(varName(mDescriptorDir), ".").asString();
        mOutputDir = params.get(varName(mOutputDir), mDescriptorDir).asString();
        mDescriptorLabelFile = params.get(varName(mDescriptorLabelFile), "./descriptorlabels.dat").asString();
        mMaxDescriptors = params.get(varName(mMaxDescriptors), 150000).asInt();
        mRebuildClusters = params.get(varName(mRebuildClusters), true).asBool();
        mRebuildPca = params.get(varName(mRebuildPca), true).asBool();
        mRebuildDescriptors = params.get(varName(mRebuildDescriptors), true).asBool();
        mDebugMode = params.get(varName(mDebugMode), false).asBool();
        mLogFile = params.get(varName(mLogFile), "./pipeline.log").asString();
        mRandomSeed = params.get(varName(mRandomSeed), 42).asInt();

        return true;
    }
}

uint32_t PipelineConfig::maxDescriptors() const
{
    return mMaxDescriptors;
}

bool PipelineConfig::setMaxDescriptors(uint32_t value)
{
    mMaxDescriptors = value;
    return setConfigParameter<uint32_t>(varName(mMaxDescriptors), value);
}

bool PipelineConfig::rebuildPca() const
{
    return mRebuildPca;
}

bool PipelineConfig::setRebuildPca(bool rebuildPca)
{
    mRebuildPca = rebuildPca;
    return setConfigParameter<bool>(varName(mRebuildPca), rebuildPca);
}

bool PipelineConfig::rebuildClusters() const
{
    return mRebuildClusters;
}

bool PipelineConfig::setRebuildClusters(bool rebuildClusters)
{
    mRebuildClusters = rebuildClusters;
    return setConfigParameter<bool>(varName(mRebuildClusters), rebuildClusters);
}

bool PipelineConfig::rebuildDescriptors() const
{
    return mRebuildDescriptors;
}

bool PipelineConfig::setRebuildDescriptors(bool rebuildDescriptors)
{
    mRebuildDescriptors = rebuildDescriptors;
    return setConfigParameter<bool>(varName(mRebuildDescriptors), rebuildDescriptors);
}

bool PipelineConfig::debugMode() const
{
    return mDebugMode;
}

bool PipelineConfig::setDebugMode(bool debugMode)
{
    mDebugMode = debugMode;
    return setConfigParameter<bool>(varName(mDebugMode), debugMode);
}

std::string PipelineConfig::toString() const
{
    std::stringstream configString;

    configString << "Output directory: " << mOutputDir << std::endl;
    configString << "Debug: " << (mDebugMode ? "true" : "false") << std::endl;
    configString << "Log file: " << mLogFile << std::endl;

    std::cout << std::endl;

    configString << "Descriptor directory: " << mDescriptorDir << std::endl;
    configString << "Descriptor labelfile: " << mDescriptorLabelFile << std::endl;
    configString << "Max. descriptors: " << mMaxDescriptors << std::endl;

    std::cout << std::endl;

    configString << "Rebuild descriptors: " << (mRebuildDescriptors ? "true" : "false") << std::endl;
    configString << "Rebuild clusters: " << (mRebuildClusters ? "true" : "false") << std::endl;
    configString << "Rebuild PCA: " << (mRebuildPca ? "true" : "false") << std::endl;

    return configString.str();
}

std::string PipelineConfig::logFile() const
{
    return mLogFile;
}

bool PipelineConfig::setLogFile(const std::string &value)
{
    mLogFile = value;
    return setConfigParameter<std::string>(varName(mLogFile), value);
}

std::string PipelineConfig::outputDirectory() const
{
    return mOutputDir;
}

bool PipelineConfig::setOutputDirectory(const std::string &outputDirectory)
{
    mOutputDir = outputDirectory;
    return setConfigParameter<std::string>(varName(mOutputDir), outputDirectory);
}

int32_t PipelineConfig::randomSeed() const
{
    return mRandomSeed;
}

bool PipelineConfig::setRandomSeed(int32_t randomSeed)
{
    mRandomSeed = randomSeed;
    return setConfigParameter<int32_t>(varName(mRandomSeed), randomSeed);
}


}

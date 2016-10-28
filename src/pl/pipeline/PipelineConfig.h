#pragma once


#include "ConfigContainer.h"

#include <string>
#include <vector>

namespace pl {

enum PipeLineMode {
    MODE_TRAIN,
    MODE_RUN,
    MODE_OPTIMIZE
};


class PipelineConfig : public ConfigContainer
{
public:
    PipelineConfig(const std::string &identifier);

    PipelineConfig(const std::string &identifier,
                   const std::string &descriptorDir,
                   const std::string &descriptorLabelFile);

    virtual ~PipelineConfig();

    std::string descriptorDir() const;
    void setDescriptorDir(const std::string &descriptorDir);

    std::string descriptorLabelFile() const;
    void setDescriptorLabelFile(const std::string &descriptorLabelFile);

    // ConfigContainer interface
    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

    unsigned int maxDescriptors() const;
    void setMaxDescriptors(unsigned int value);

    bool rebuildPca() const;
    void setRebuildPca(bool rebuildPca);

    bool rebuildClusters() const;
    void setRebuildClusters(bool rebuildClusters);

    bool rebuildDescriptors() const;
    void setRebuildDescriptors(bool rebuildDescriptors);

    PipeLineMode pipelineMode() const;
    void setPipelineMode(const PipeLineMode &pipelineMode);
    void setPipelineMode(const std::string &pipelineMode);

    bool debugMode() const;
    void setDebugMode(bool debugMode);

    PipeLineMode str2mode(const std::string &modeString) const;

    std::string mode2string(const PipeLineMode &mode) const;

    std::string logFile() const;
    void setLogFile(const std::string &value);

    std::string outputDirectory() const;
    void setOutputDirectory(const std::string &outputDirectory);

    int randomSeed() const;
    void setRandomSeed(int randomSeed);

private:
    /**
     * @brief mIdentifier: Identifier string (preparation for config parsing from file)
     */
    std::string mIdentifier;

    /**
     * @brief descriptorDir
     */
    std::string mDescriptorDir;

    /**
     * @brief mOutputDirectory
     */
    std::string mOutputDir;

    /**
     * @brief descriptorLabelFile
     */
    std::string mDescriptorLabelFile;

    /**
     * @brief maxDescriptors
     */
    unsigned int mMaxDescriptors;

    /**
     * @brief mRebuildDescriptors
     */
    bool mRebuildDescriptors;

    /**
     * @brief mRebuildClusters
     */
    bool mRebuildClusters;

    /**
     * @brief mRebuildPca
     */
    bool mRebuildPca;

    /**
     * @brief mPipelineMode
     */
    PipeLineMode mPipelineMode;

    /**
     * @brief mDebugMode
     */
    bool mDebugMode;

    /**
     * @brief logFile
     */
    std::string mLogFile;

    /**
     * @brief mRandomSeed
     */
    int mRandomSeed;
};


}

#pragma once


#include "ConfigContainer.h"

#include <string>
#include <vector>

namespace pl {


class PipelineConfig : public ConfigContainer
{
public:
    PipelineConfig(const std::string &identifier);

    PipelineConfig(const std::string &identifier,
                   const std::string &descriptorDir,
                   const std::string &descriptorLabelFile);

    virtual ~PipelineConfig();

    std::string descriptorDir() const;
    bool setDescriptorDir(const std::string &descriptorDir);

    std::string descriptorLabelFile() const;
    bool setDescriptorLabelFile(const std::string &descriptorLabelFile);

    // ConfigContainer interface
    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

    uint32_t maxDescriptors() const;
    bool setMaxDescriptors(uint32_t value);

    bool rebuildPca() const;
    bool setRebuildPca(bool rebuildPca);

    bool rebuildClusters() const;
    bool setRebuildClusters(bool rebuildClusters);

    bool rebuildDescriptors() const;
    bool setRebuildDescriptors(bool rebuildDescriptors);

    bool debugMode() const;
    bool setDebugMode(bool debugMode);

    std::string logFile() const;
    bool setLogFile(const std::string &value);

    std::string outputDirectory() const;
    bool setOutputDirectory(const std::string &outputDirectory);

    int32_t randomSeed() const;
    bool setRandomSeed(int32_t randomSeed);

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
    uint32_t mMaxDescriptors;

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
    int32_t mRandomSeed;
};


}

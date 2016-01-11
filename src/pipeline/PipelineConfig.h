#pragma once


#include "ConfigContainer.h"

#include <string>
#include <vector>

namespace pl {


class PipelineConfig : public ConfigContainer
{
public:
    PipelineConfig();
    virtual ~PipelineConfig();

    std::string descriptorDir() const;
    void setDescriptorDir(const std::string &descriptorDir);

    std::string descriptorLabelFile() const;
    void setDescriptorLabelFile(const std::string &descriptorLabelFile);

    std::string dimensionalityReductionPath() const;
    void setDimensionalityReductionPath(const std::string &dimensionalityReductionPath);

    int dimensionalityReductionSubset() const;
    void setDimensionalityReductionSubset(int dimensionalityReductionSubset);

private:
    /**
     * @brief descriptorDir
     */
    std::string mDescriptorDir;

    /**
     * @brief descriptorLabelFile
     */
    std::string mDescriptorLabelFile;

    /**
     * @brief vocabs
     */
    std::vector<std::string> mVocabs;

    /**
     * @brief mDimensionalityReductionPath
     */
    std::string mDimensionalityReductionPath;

    /**
     * @brief mDimensionalityReductionSubset
     */
    int mDimensionalityReductionSubset;

    // ConfigContainer interface
    virtual std::string toString() const;
};


}

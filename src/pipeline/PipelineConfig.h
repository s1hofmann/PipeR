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
    void setDescriptorDir(const std::string &descriptorDir);

    std::string descriptorLabelFile() const;
    void setDescriptorLabelFile(const std::string &descriptorLabelFile);

    // ConfigContainer interface
    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

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
     * @brief descriptorLabelFile
     */
    std::string mDescriptorLabelFile;

    /**
     * @brief vocabs
     */
    std::vector<std::string> mVocabs;
};


}

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

    std::string pca() const;
    void setPca(const std::string &pca);

    std::vector<std::string> vocabs() const;
    void setVocabs(const std::vector<std::string> &vocabs);

    std::string descriptorLabelFile() const;
    void setDescriptorLabelFile(const std::string &descriptorLabelFile);

    std::string descriptorDir() const;
    void setDescriptorDir(const std::string &descriptorDir);

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
     * @brief pca
     */
    std::string mPca;
};


}

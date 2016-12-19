#pragma once

#include "MLConfig.h"
#include "../core/vlfeat/wrapper/sgdsolver.h"
#include <opencv2/core/core.hpp>

namespace pl {


class NCConfig : public MLConfig
{
public:
    NCConfig(const std::string &identifier,
             const std::vector<std::string> &outputFiles = std::vector<std::string>());

    virtual ~NCConfig();

    cv::Mat1d means() const;
    void setMeans(const cv::Mat1d &means);

    std::vector<std::string> classifierFiles() const;
    bool setClassifierFiles(const std::vector<std::string> &classifierFile);

    // ConfigContainer interface
    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

private:
    cv::Mat1d mMeans;

    std::vector<std::string> mClassifierFiles;
};


}

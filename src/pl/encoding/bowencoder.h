#pragma once

#include "EncodingStep.h"
#include "bowconfig.h"

#include "../core/clustering/kmeanscluster.h"
#include "../core/encoding/bowencoder.h"
#include "descriptorpyramid.h"

namespace pl {


class BOWEncodeingStep : public EncodingStep
{
public:
    BOWEncodeingStep(const cv::Ptr<ConfigContainer> config);

    virtual cv::Mat runImpl(const bool debugMode,
                            const cv::Mat &input,
                            const cv::Mat &param) const;

    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &param) const;
private:
    cv::Mat encode(const std::string &encoder, const cv::Mat &data) const;

    cv::Mat encodePyramid(const std::string &encoder, const cv::Mat &data) const;
};


}

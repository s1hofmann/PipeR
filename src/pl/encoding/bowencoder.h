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
    BOWEncodeingStep(const cv::Ptr<BOWConfig> config);

    // PipelineStep interface
    virtual cv::Mat train(const cv::Mat &input, const cv::Mat &param) const override;
    virtual cv::Mat run(const cv::Mat &input, const cv::Mat &param) const override;
    virtual cv::Mat debugTrain(const cv::Mat &input, const cv::Mat &param) const override;
    virtual cv::Mat debugRun(const cv::Mat &input, const cv::Mat &param) const override;

private:
    cv::Mat encode(const std::string &encoder, const cv::Mat &data) const;

    cv::Mat encodePyramid(const std::string &encoder, const cv::Mat &data) const;
};


}

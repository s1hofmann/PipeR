#pragma once

#include <opencv2/core/core.hpp>

namespace pl {


class Metrics
{
public:
    Metrics();

    static uint32_t truePositives(const cv::Mat1d predictions,
                                      const cv::Mat1d labels);
    static uint32_t falsePositives(const cv::Mat1d predictions,
                                       const cv::Mat1d labels);

    static uint32_t trueNegatives(const cv::Mat1d predictions,
                                      const cv::Mat1d labels);
    static uint32_t falseNegatives(const cv::Mat1d predictions,
                                       const cv::Mat1d labels);

    static double precision(const cv::Mat1d predictions,
                            const cv::Mat1d labels);
    static double recall(const cv::Mat1d predictions,
                         const cv::Mat1d labels);

    static double f1(const cv::Mat1d predictions,
                     const cv::Mat1d labels);
};


}

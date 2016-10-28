#pragma once

#include <opencv2/core/core.hpp>

namespace pl {


class Metrics
{
public:
    Metrics();

    static unsigned int truePositives(const cv::Mat1d predictions,
                                      const cv::Mat1d labels);
    static unsigned int falsePositives(const cv::Mat1d predictions,
                                       const cv::Mat1d labels);

    static unsigned int trueNegatives(const cv::Mat1d predictions,
                                      const cv::Mat1d labels);
    static unsigned int falseNegatives(const cv::Mat1d predictions,
                                       const cv::Mat1d labels);

    static double precision(const cv::Mat1d predictions,
                            const cv::Mat1d labels);
    static double recall(const cv::Mat1d predictions,
                         const cv::Mat1d labels);

    static double f1(const cv::Mat1d predictions,
                     const cv::Mat1d labels);
};


}

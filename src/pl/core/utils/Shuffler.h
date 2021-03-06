#pragma once

#include <opencv2/core/core.hpp>

#include "../../pipeline/globals.h"
#include "Range.h"


namespace pl {


class Shuffler
{
public:
    Shuffler();

    static void shuffle(const cv::Mat &descriptors,
                        const cv::Mat &labels,
                        cv::Mat &shuffledDescriptors,
                        cv::Mat &shuffledLabels);

    static void shuffle(const std::vector<std::string> &files,
                        const std::vector<int32_t> &labels,
                        std::vector<std::string> &shuffledFiles,
                        std::vector<int32_t> &shuffledLabels);
};


}

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
};


}

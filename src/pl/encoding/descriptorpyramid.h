#pragma once

#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>

namespace pl {


class DescriptorPyramid
{
public:
    explicit DescriptorPyramid(int32_t levels = 1) {
        this->levels = levels;
    }

    std::vector<cv::Mat> build(const cv::Mat1f &descriptor);

private:
    int32_t totalElements(int32_t level);
    std::vector<cv::Mat> split(const cv::Mat &input);

private:
    int32_t levels = 1;
};


}

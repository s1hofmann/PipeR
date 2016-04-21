#include "descriptorpyramid.h"

namespace pl {


std::vector<cv::Mat> DescriptorPyramid::build(const cv::Mat1f &descriptor)
{
    int maxIndex = totalElements(this->levels);

    std::vector<cv::Mat> ret = {descriptor};

    for(int i = 0; i < maxIndex; ++i) {
        std::vector<cv::Mat> tmp = split(ret[i]);
        std::copy(tmp.begin(), tmp.end(), std::back_inserter(ret));
    }

    return ret;
}


int DescriptorPyramid::totalElements(int level)
{
    int total = 0;

    for(int i = 0; i < level; ++i) {
        total += static_cast<int>(pow(4.0,i));
    }

    return total;
}


std::vector<cv::Mat> DescriptorPyramid::split(const cv::Mat &input)
{
    std::vector<cv::Mat> ret(4);

    if(input.empty()) {
        return ret;
    }

    cv::Mat1f xCoords = input.colRange(input.cols - 2, input.cols - 1);
    cv::Mat1f yCoords = input.colRange(input.cols - 1, input.cols);

    //Split into left/right half
    cv::Mat1i xIdx;
    cv::sortIdx(xCoords, xIdx, cv::SORT_ASCENDING + cv::SORT_EVERY_COLUMN);

    int maxIdx = xIdx(xIdx.rows - 1);
    int minIdx = xIdx(0);
    float maxCoord = xCoords.at<float>(maxIdx);
    float minCoord = xCoords.at<float>(minIdx);

    int threshold = (maxCoord - minCoord)/2;

    cv::Mat left, right;
    for(int i = 0; i < input.rows; ++i) {
        if(xCoords.at<float>(xIdx(i)) < (minCoord + threshold)) {
            left.push_back(input.row(xIdx(i)));
        } else {
            right.push_back(input.row(xIdx(i)));
        }
    }
    ret[0] = left;
    ret[1] = right;

    //Split into top/bottom half
    cv::Mat1i yIdx;
    cv::sortIdx(input.col(input.cols - 1), yIdx, cv::SORT_ASCENDING + cv::SORT_EVERY_COLUMN);

    maxIdx = yIdx(yIdx.rows - 1);
    minIdx = yIdx(0);
    maxCoord = yCoords.at<float>(maxIdx);
    minCoord = yCoords.at<float>(minIdx);

    threshold = (maxCoord - minCoord)/2;

    cv::Mat top, bottom;
    for(int i = 0; i < input.rows; ++i) {
        if(yCoords.at<float>(yIdx(i)) < (minCoord + threshold)) {
            top.push_back(input.row(yIdx(i)));
        } else {
            bottom.push_back(input.row(yIdx(i)));
        }
    }
    ret[2] = top;
    ret[3] = bottom;

    return ret;
}


}

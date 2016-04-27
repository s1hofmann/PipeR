#pragma once

#include <string>
#include <vector>
#include <set>
#include <opencv2/core/core.hpp>

namespace pl {


class EvaluationObject
{
public:
    EvaluationObject(const std::string &mFileName,
                     const std::vector<cv::Rect> &boundingBoxes,
                     const std::vector<std::vector<cv::Point>> &contours);

    ~EvaluationObject() { }

    inline std::string getFileName() const { return mFileName; }
    inline std::vector<cv::Rect> getBoundingBoxes() const { return mBoundingBoxes; }
    inline std::vector<std::vector<cv::Point>> getContours() const { return mContours; }

private:
    std::string mFileName;
    std::vector<cv::Rect> mBoundingBoxes;
    std::vector<std::vector<cv::Point>> mContours;
};


}

#include "evaluationobject.h"

#include <string>
#include <iostream>

namespace pl {


EvaluationObject::EvaluationObject(const std::string &fileName,
                                   const std::vector<cv::Rect> &boundingBoxes,
                                   const std::vector<std::vector<cv::Point> > &contours)
{
    mFileName = fileName;
    mBoundingBoxes = boundingBoxes;
    mContours = contours;
}


}

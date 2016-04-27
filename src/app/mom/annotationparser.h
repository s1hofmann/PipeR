#pragma once

#include <vector>
#include <set>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "evaluationobject.h"

namespace pl {


class AnnotationParser
{
public:
    AnnotationParser();

    virtual std::vector<EvaluationObject> parse(const std::string &fileName) const = 0;

protected:
    /**
     * @brief split Splits a \link{std::string} at a given delimiter and returns a \link{std::vector} of every part
     * @param input \link{std::string} to split
     * @param delim \link{char} delimiter
     * @return \link{std::vector}<\link{std::string}>
     */
    std::vector<std::string> split(const std::string &input, const char delim = ' ') const;

    /**
     * @brief splitUnique Splits a \link{std::string} at a given delimiter and returns a \link{std::set} of unique \link{std::string}
     * @param input \link{std::string} to split
     * @param delim \link{char} delimiter
     * @return \link{std::set}<\link{std::string}>
     */
    std::set<std::string> splitUnique(const std::string &input, const char delim = ' ') const;

    /**
     * @brief createBoundingBox Creates a \link{cv::Rect} bounding box out of an annotation string
     * @param annotation \link{std::string} representation of the bounding box
     * @return \link{cv::Rect}
     */
    virtual cv::Rect createBoundingBox(const std::string &annotation) const = 0;

    /**
     * @brief createContour Creates a \link{std::vector}<\link{cv::Point}> bounding contour out of an annotation string
     * @param annotation \link{std::string} representation of the contour
     * @return \link{std::vector}<\link{cv::Point}>
     */
    virtual std::vector<cv::Point> createContour(const std::string &annotation) const = 0;
};


}

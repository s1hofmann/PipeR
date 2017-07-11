#include "annotationparser.h"

namespace pl {

AnnotationParser::AnnotationParser()
{

}

std::vector<std::string> AnnotationParser::split(const std::string &input,
                                                 const char delim) const
{
    if(input.empty()) {
        return std::vector<std::string>();
    }

    std::string buf;
    std::vector<std::string> splits;

    for(size_t idx = 0; idx < input.length(); ++idx) {
        if(input[idx] != delim) {
            buf += input[idx];
        } else {
            if(buf.length() > 0) {
                splits.push_back(buf);
                buf = "";
            }
        }
    }
    splits.push_back(buf);
    buf = "";

    return splits;
}


std::set<std::string> AnnotationParser::splitUnique(const std::string &input,
                                                    const char delim) const
{
    if(input.empty()) {
        return std::set<std::string>();
    }

    std::string buf;
    std::set<std::string> splits;

    for(size_t idx = 0; idx < input.length(); ++idx) {
        if(input[idx] != delim) {
            buf += input[idx];
        } else {
            if(buf.length() > 0) {
                splits.insert(buf);
                buf = "";
            }
        }
    }
    splits.insert(buf);
    buf = "";

    return splits;
}


cv::Rect AnnotationParser::createBoundingBox(const std::string &annotation) const
{
    std::vector<std::string> strCoords = split(annotation, ',');

    return cv::Rect(std::stoi(strCoords[0]),
                    std::stoi(strCoords[1]),
                    std::stoi(strCoords[2]),
                    std::stoi(strCoords[3]));
}

std::vector<cv::Point> AnnotationParser::createContour(const std::string &annotation) const
{
    std::vector<std::string> strPoints = split(annotation, ',');

    std::vector<cv::Point> contour;
    for(size_t idx = 0; idx < strPoints.size(); idx += 2) {
        contour.push_back(cv::Point(std::stoi(strPoints[idx]), std::stoi(strPoints[idx+1])));
    }

    return contour;
}


}

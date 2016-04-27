#pragma once

#include "annotationparser.h"
#include <iostream>
#include <string>
#include <QDomDocument>
#include <QFile>
#include <QString>

namespace pl {


class MOMParser : public AnnotationParser
{
public:
    MOMParser();

    virtual std::vector<EvaluationObject> parse(const std::string &fileName) const;

    // AnnotationParser interface
protected:
    virtual cv::Rect createBoundingBox(const std::string &annotation) const;
    virtual std::vector<cv::Point> createContour(const std::string &annotation) const;
};


}

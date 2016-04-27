#pragma once

#include <iostream>
#include <string>
#include <QDomDocument>
#include <QFile>
#include <QString>

#include <type_traits>

#include "evaluationobject.h"
#include "momparser.h"

namespace pl {


template <typename T>
class AnnotationFile
{
public:
    static_assert(std::is_base_of<AnnotationParser, T>::value, "AnnotationParser type needed");
    AnnotationFile() {

    }

    ~AnnotationFile() {

    }

    static std::vector<EvaluationObject> open(const std::string &annotationFile) {
        T parser;
        return parser.parse(annotationFile);
    }
};


}

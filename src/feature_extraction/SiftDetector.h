//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "FeatureExtractionStep.h"

namespace pipe {

class SiftDetector : public FeatureExtractionStep {
public:
    SiftDetector(const std::string &info = "SIFT feature extractor",
                 const std::string &usage = "TODO: SIFT parameters",
                 const std::string &help = "This feature extractor runs D. Lowes Scale Invariant Feature Transform (SIFT)");

    virtual ~SiftDetector();

    virtual cv::Mat train();
    virtual cv::Mat run();
};


}

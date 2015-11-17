//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include <iostream>
#include "PreprocessingStep.h"

namespace pipe {


class ImageProcessingStep : public PreprocessingStep {
public:
    ImageProcessingStep(const std::string &info = "Image preprocessing method",
                        const std::string &usage = "List parameters here.",
                        const std::string &help = "Detailed method description goes here.");

    virtual cv::Mat train();
    virtual cv::Mat run();

    virtual ~ImageProcessingStep();

private:

};


}

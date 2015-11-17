//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "PreprocessingStep.h"

namespace pipe {


class MaskGenerationStep : public PreprocessingStep {
public:
    MaskGenerationStep(const std::string &info = "Mask generation preprocessing method",
                       const std::string &usage = "Parameter description goes here.",
                       const std::string &help = "Detailed description goes here.");

    virtual ~MaskGenerationStep();

    virtual cv::Mat train();
    virtual cv::Mat run();

private:

};


}

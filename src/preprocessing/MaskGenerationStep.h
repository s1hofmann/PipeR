//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "PreprocessingStep.h"

namespace pipe {


class MaskGenerationStep : public PreprocessingStep {
public:
    MaskGenerationStep(const cv::Ptr<ConfigContainer> config,
                       const std::string &info = "Mask generation preprocessing method");

    virtual ~MaskGenerationStep();

    //FIXME: Should still be pure virtual, just for debugging
    virtual cv::Mat train();
    virtual cv::Mat run();

private:

};


}

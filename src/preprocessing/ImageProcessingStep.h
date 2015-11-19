//
// Created by Simon Hofmann on 17.11.15.
//


#pragma once

#include "PreprocessingStep.h"

namespace pipe {


class ImageProcessingStep : public PreprocessingStep {
public:
    ImageProcessingStep(const cv::Ptr<ConfigContainer> config,
                        const std::string &info = "Image preprocessing method");

    //FIXME: Should still be pure virtual, only for debugging
    virtual cv::Mat train();
    virtual cv::Mat run();

    virtual ~ImageProcessingStep();

private:

};


}

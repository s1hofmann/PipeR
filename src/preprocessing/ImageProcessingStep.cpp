//
// Created by Simon Hofmann on 17.11.15.
//

#include "ImageProcessingStep.h"

namespace pipe {


ImageProcessingStep::ImageProcessingStep(const std::string &info,
                                         const std::string &usage,
                                         const std::string &help)
    :
        PreprocessingStep(info, usage, help)
{

}


int ImageProcessingStep::execute() {
    std::cout << "HI!" << std::endl;
    return 0;
}

ImageProcessingStep::~ImageProcessingStep() {

}

}

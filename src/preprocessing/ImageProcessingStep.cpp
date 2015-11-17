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


ImageProcessingStep::~ImageProcessingStep() {

}


cv::Mat ImageProcessingStep::train() {
    return cv::Mat();
}


cv::Mat ImageProcessingStep::run() {
    return cv::Mat();
}


}

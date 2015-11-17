//
// Created by Simon Hofmann on 18.11.15.
//

#include "VladEncoder.h"

namespace pipe {


VladEncoder::VladEncoder(const std::string &info,
                         const std::string &usage,
                         const std::string &help)
:
    EncodingStep(info, usage, help)
{

}


VladEncoder::~VladEncoder()
{

}


cv::Mat VladEncoder::train()
{
    return cv::Mat();
}


cv::Mat VladEncoder::run()
{
    return cv::Mat();
}


}

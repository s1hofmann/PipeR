//
// Created by Simon Hofmann on 18.11.15.
//


#pragma once

#include "EncodingStep.h"

namespace pl {


class VladEncoder : public EncodingStep {
public:
    VladEncoder(const std::string &info = "VLAD encoding",
                const std::string &usage = "Needed parameters: cluster centers.",
                const std::string &help = "Vector Of Locally Aggregated Descriptors (VLAD) encoding method.");

    virtual ~VladEncoder();

    virtual cv::Mat train();
    virtual cv::Mat run();

private:

};


}


//
// Created by Simon Hofmann on 25.12.15.
//

#pragma once

#include "IOImpl.h"

namespace pl {


class YML : public IOImpl
{
public:
    YML();
    virtual ~YML();

    // IOImpl interface
    virtual bool write(const cv::Mat &output,
               const std::string &outPath,
               const std::string &fileName) const;

    virtual cv::Mat read(const std::string &input) const;
};


}

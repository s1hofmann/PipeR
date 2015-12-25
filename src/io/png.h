//
// Created by Simon Hofmann on 25.12.15.
//

#pragma once


#include "IOImpl.h"


namespace pl {


class PNG : public IOImpl
{
public:
    PNG();
    virtual ~PNG();

    // IOImpl interface
    bool write(const cv::Mat &output,
               const std::string &outPath,
               const std::string &fileName) const;

    cv::Mat read(const std::string &input) const;
};


}

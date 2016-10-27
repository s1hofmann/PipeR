//
// Created by Simon Hofmann on 25.12.15.
//

#pragma once

#include "IOImpl.h"


namespace pl {


class BIN : public IOImpl
{
public:
    BIN();
    virtual ~BIN();

    // IOImpl interface
    virtual unsigned long write(const cv::Mat &output,
                                const std::string &outPath,
                                const std::string &fileName,
                                const std::string &prefix = std::string()) const;

    virtual cv::Mat read(const std::string &input,
                         const std::string &prefix = std::string()) const;
};


}

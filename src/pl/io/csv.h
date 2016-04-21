#pragma once

#include "IOImpl.h"

namespace pl {


class CSV : public IOImpl
{
public:
    CSV();
    virtual ~CSV();

    // IOImpl interface
    unsigned long write(const cv::Mat &output,
                        const std::string &outPath,
                        const std::string &fileName) const;

    cv::Mat read(const std::string &input) const;
};


}

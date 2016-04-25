#pragma once

#include "encodingmethod.h"

namespace pl {


class BOWEncoder : public EncodingMethod
{
public:
    BOWEncoder();

    // EncodingMethod interface
    virtual cv::Mat encode(const cv::Mat &data) override;
    virtual void loadData(const std::string &fileName) override;

private:
    cv::Mat1f mMeans;
};


}

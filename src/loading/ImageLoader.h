//
// Created by Simon Hofmann on 13.12.15.
//


#pragma once

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>

namespace pipe {


class ImageLoader {
public:
    ImageLoader();

    virtual ~ImageLoader();

    std::vector<cv::Mat> load(const std::string &path, const string &filter) const;
};


}

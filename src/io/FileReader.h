//
// Created by Simon Hofmann on 13.12.15.
//


#pragma once

#include <vector>
#include <utility>
#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../core/utils/progressbar.h"
#include "IOImpl.h"
#include "bin.h"
#include "img.h"
#include "yml.h"


namespace pl {


template <class T>
class FileReader {
    static_assert(std::is_base_of<IOImpl, T>::value, "IOImpl type needed");

public:
    FileReader() {}

    virtual ~FileReader() {}

    virtual cv::Mat read(const std::string &input)
    {
        T reader;

        return reader.read(input);
    }
};


}

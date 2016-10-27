//
// Created by Simon Hofmann on 13.12.15.
//


#pragma once

#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <type_traits>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../core/utils/progressbar.h"
#include "IOImpl.h"
#include "bin.h"
#include "img.h"
#include "yml.h"


namespace pl {


template <typename T>
class FileReader {
public:
    FileReader() {
        static_assert(std::is_base_of<IOImpl, T>::value, "IOImpl type needed");
    }

    virtual ~FileReader() {}

    virtual cv::Mat read(const std::string &input,
                         const std::string &prefix = std::string()) const
    {
        T reader;

        try {
            return reader.read(input,
                               prefix);
        } catch(std::runtime_error) {
            throw;
        }
    }
};


}

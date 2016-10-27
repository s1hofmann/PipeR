#pragma once

#include <opencv2/core/core.hpp>
#include <string>
#include <type_traits>

#include "IOImpl.h"
#include "bin.h"
#include "img.h"
#include "yml.h"


namespace pl {


template <typename T>
class FileWriter
{
public:
    FileWriter() {
        static_assert(std::is_base_of<IOImpl, T>::value, "IOImpl type needed");
    }

    virtual ~FileWriter() {}

    bool write(const cv::Mat &output,
               const std::string &path,
               const std::string &fileName,
               const std::string &prefix = std::string()) const
    {
        T writer;
        try {
            unsigned long result = writer.write(output,
                                                path,
                                                fileName,
                                                prefix);

            return (result > 0) ? true : false;
        } catch(std::runtime_error) {
            throw;
        }
    }
};


}

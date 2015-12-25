#pragma once

#include <opencv2/core/core.hpp>
#include <string>

#include "IOImpl.h"
#include "bin.h"
#include "img.h"
#include "yml.h"


namespace pl {


template <class T>
class FileWriter
{
    static_assert(std::is_base_of<IOImpl, T>::value, "IOImpl type needed");
public:
    FileWriter() {}
    virtual ~FileWriter() {}

    bool write(const cv::Mat &output,
               const std::string &path,
               const std::string &fileName) const
    {
        T writer;
        return writer.write(output,
                            path,
                            fileName);
    }
};


}

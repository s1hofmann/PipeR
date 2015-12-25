#pragma once

#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <qt/QtCore/QFile>
#include <qt/QtCore/QFileInfo>
#include <qt/QtCore/QFileInfoList>
#include <qt/QtCore/QString>
#include <qt/QtCore/QDir>
#include <qt/QtCore/QTextStream>

namespace pl {

class IOImpl
{
public:
    IOImpl();
    virtual ~IOImpl();

    virtual bool write(const cv::Mat &output,
                       const std::string &outPath,
                       const std::string &fileName) const = 0;

    virtual cv::Mat read(const std::string &input) const = 0;
};


}

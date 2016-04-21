#pragma once

#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QString>
#include <QDir>
#include <QTextStream>

#include "../pipeline/globals.h"
#include "../exception/error.h"

namespace pl {

class IOImpl
{
public:
    IOImpl();
    virtual ~IOImpl();

    virtual unsigned long write(const cv::Mat &output,
                                const std::string &outPath,
                                const std::string &fileName) const = 0;

    virtual cv::Mat read(const std::string &input) const = 0;
};


}

#pragma once

#include <vector>
#include <string>
#include <utility>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <qt/QtCore/QFile>
#include <qt/QtCore/QFileInfo>
#include <qt/QtCore/QFileInfoList>
#include <qt/QtCore/QString>
#include <qt/QtCore/QDir>
#include <qt/QtCore/QTextStream>

#include "FileReader.h"

#include "../core/utils/progressbar.h"

namespace pl {


class FileUtil
{
public:
    FileUtil();

    virtual ~FileUtil();

    std::vector<cv::Mat> loadImages(const std::string &path);

    std::pair<std::vector<cv::Mat>, std::vector<int>> loadImagesFromLabelFile(const std::string &labelFile);

    std::vector<std::string> getFiles(const std::string &path);

    std::pair<std::vector<std::string>, std::vector<int>> getFilesFromLabelFile(const std::string &labelFile);

private:
    std::vector<std::string> examineDirectory(const std::string &pathName) const;
};


}

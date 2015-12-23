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

#include <qt/QtCore/QFile>
#include <qt/QtCore/QFileInfo>
#include <qt/QtCore/QFileInfoList>
#include <qt/QtCore/QString>
#include <qt/QtCore/QDir>
#include <qt/QtCore/QTextStream>

namespace pl {


class ImageLoader {
public:
    ImageLoader();

    virtual ~ImageLoader();

    std::vector<cv::Mat> loadImages(const std::string &path);

    std::pair<std::vector<cv::Mat>, std::vector<int>> loadImagesFromLabelFile(const std::string &labelFile);

    std::vector<std::string> getFiles(const std::string &path);

    std::pair<std::vector<std::string>, std::vector<int>> getFilesFromLabelFile(const std::string &labelFile);
private:
    std::vector<std::string> examineDirectory(const std::string &path);
};


}

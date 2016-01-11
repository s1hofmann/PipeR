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
#include "FileWriter.h"

#include "../core/utils/progressbar.h"

namespace pl {


class FileUtil
{
public:
    FileUtil();

    virtual ~FileUtil();

    /**
     * @brief loadImages Returns an \link{std::vector} of \link{cv::Mat} objects containing all images in a given folder.
     * @param path Folder to load images from
     * @return \link{std::vector}<\link{cv::Mat}>
     */
    std::vector<cv::Mat> loadImages(const std::string &path);

    /**
     * @brief loadImagesFromLabelFile Returns a \link{std::pair} of \link{std::vector}<\link{cv::Mat}> and \link{std::vector}<int>} read from a labelfile
     * @param labelFile Labelfile to read data from
     * @return \link{std::pair}<\link{std::vector}<\link{cv::Mat}>, \link{std::vector}<int>>
     */
    std::pair<std::vector<cv::Mat>, std::vector<int>> loadImagesFromLabelFile(const std::string &labelFile);

    /**
     * @brief getFiles Returns an \link{std::vector} of \link{std::string} objects containing all files in a given folder.
     * @param path Folder to get files from
     * @return \link{std::vector}<\link{std::string}>
     */
    std::vector<std::string> getFiles(const std::string &path);

    /**
     * @brief getFilesFromLabelFile Returns a \link{std::pair} of \link{std::vector}<\link{std::string}> and \link{std::vector}<int>, holding filenames and corresponding labels read from a given labelfile
     * @param labelFile File to read data from
     * @return \link{std::pair}<\link{std::vector}<\link{std::string}>, \link{std::vector}<int>>
     */
    std::pair<std::vector<std::string>, std::vector<int>> getFilesFromLabelFile(const std::string &labelFile);

    /**
     * @brief saveImage
     * @param image
     * @param outputPath
     * @param imageFileName
     * @return
     */
    bool saveImage(const cv::Mat &image,
                   const std::string &outputPath,
                   const std::string &imageFileName) const;

    cv::Mat loadImage(const std::string &fileName) const;

    /**
     * @brief saveBinary
     * @param data
     * @param outputPath
     * @param fileName
     * @return
     */
    bool saveBinary(const cv::Mat &data,
                    const std::string &outputPath,
                    const std::string &fileName) const;

    /**
     * @brief saveYML
     * @param data
     * @param outputPath
     * @param fileName
     * @return
     */
    bool saveYML(const cv::Mat &data,
                 const std::string &outputPath,
                 const std::string &fileName) const;

    /**
     * @brief saveDescriptorWithLabel
     * @param descriptor
     * @param label
     * @param outputPath
     * @param descriptorFileName
     * @param labelFileName
     * @return
     */
    bool saveDescriptorWithLabel(const cv::Mat &descriptor,
                                 const int label,
                                 const std::string &outputPath,
                                 const std::string &descriptorFileName,
                                 const std::string &labelFileName) const;

    /**
     * @brief saveDescriptor
     * @param descriptor
     * @param outputPath
     * @param fileName
     * @return
     */
    bool saveDescriptor(const cv::Mat &descriptor,
                        const std::string &outputPath,
                        const std::string &fileName) const;

private:
    /**
     * @brief examineDirectory
     * @param pathName
     * @return
     */
    std::vector<std::string> examineDirectory(const std::string &pathName) const;

    /**
     * @brief appendDescriptor
     * @param labelFilePath
     * @param labelFileName
     * @param fileName
     * @param label
     * @return
     */
    bool appendDescriptor(const std::string &labelFilePath,
                          const std::string &labelFileName,
                          const std::string &fileName,
                          const int label) const;
};


}

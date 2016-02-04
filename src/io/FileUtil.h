#pragma once

#include <vector>
#include <string>
#include <sstream>
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
#include "../pipeline/globals.h"

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
    static std::vector<cv::Mat> loadImages(const std::string &path);

    /**
     * @brief loadImagesFromLabelFile Returns a \link{std::pair} of \link{std::vector}<\link{cv::Mat}> and \link{std::vector}<int>} read from a labelfile
     * @param labelFile Labelfile to read data from
     * @return \link{std::pair}<\link{std::vector}<\link{cv::Mat}>, \link{std::vector}<int>>
     */
    static std::pair<std::vector<cv::Mat>, std::vector<int>> loadImagesFromLabelFile(const std::string &labelFile);

    /**
     * @brief getFiles Returns an \link{std::vector} of \link{std::string} objects containing all files in a given folder.
     * @param path Folder to get files from
     * @return \link{std::vector}<\link{std::string}>
     */
    static std::vector<std::string> getFiles(const std::string &path);

    /**
     * @brief getFilesFromLabelFile Returns a \link{std::pair} of \link{std::vector}<\link{std::string}> and \link{std::vector}<int>, holding filenames and corresponding labels read from a given labelfile
     * @param labelFile File to read data from
     * @return \link{std::pair}<\link{std::vector}<\link{std::string}>, \link{std::vector}<int>>
     */
    static std::pair<std::vector<std::string>, std::vector<int>> getFilesFromLabelFile(const std::string &labelFile);

    /**
     * @brief saveImage Utility function to save a \link{cv::Mat} as image
     * @param image \link{cv::Mat} to save
     * @param outputPath \link{std::string} containing the output path
     * @param imageFileName \link{std::string} containing the filename
     * @return boolean value if file was written or not
     */
    static bool saveImage(const cv::Mat &image,
                          const std::string &outputPath,
                          const std::string &imageFileName);

    /**
     * @brief loadImage Utility function to load an image into a \link{cv::Mat} object
     * @param fileName \link{std::string} containing the absolute path to the file
     * @return Success: \link{cv::Mat} object containing the image\n Failure: Empty \link{cv::Mat}
     */
    static cv::Mat loadImage(const std::string &fileName);

    /**
     * @brief saveBinary Utility function to save a \link{cv::Mat} in binary format
     * @param data \link{cv::Mat} to save
     * @param outputPath \link{std::string} containing the output path
     * @param imageFileName \link{std::string} containing the filename
     * @return boolean value if file was written or not
     */
    static bool saveBinary(const cv::Mat &data,
                           const std::string &outputPath,
                           const std::string &fileName);

    /**
     * @brief saveYML Utility function to save a \link{cv::Mat} in YML format
     * @param data \link{cv::Mat} to save
     * @param outputPath \link{std::string} containing the output path
     * @param imageFileName \link{std::string} containing the filename
     * @return boolean value if file was written or not
     */
    static bool saveYML(const cv::Mat &data,
                        const std::string &outputPath,
                        const std::string &fileName);

    /**
     * @brief saveDescriptorWithLabel Utility function which saves a descriptor in binary format and appends its label to a labelfile
     * @param descriptor \link{cv::Mat} to save
     * @param label Corresponding label
     * @param outputPath \link{std::string} containing the output path
     * @param descriptorFileName \link{std::string} containing the filename to save
     * @param labelFileName \link{std::string} containing the absolute path to the label file
     * @return boolean value if descriptor was written or not
     */
    static bool saveDescriptorWithLabel(const cv::Mat &descriptor,
                                        const int label,
                                        const std::string &outputPath,
                                        const std::string &descriptorFileName,
                                        const std::string &labelFileName);

    /**
     * @brief saveDescriptor Utility function which saves a descriptor in binary format
     * @param descriptor \link{cv::Mat} to save
     * @param outputPath \link{std::string} containing the output path
     * @param fileName \link{std::string} containing the filename to save
     * @return boolean value if descriptor was written or not
     */
    static bool saveDescriptor(const cv::Mat &descriptor,
                               const std::string &outputPath,
                               const std::string &fileName);

    /**
     * @brief getFilename Utility function which returns the filename from a passed absolute file path
     * @param path \link{std::string} containing the full file path to extract the filename from
     * @return  Sucess: \link{std::string} containing the filename\n Failure: Empty \link{std::string}
     */
    static std::string getFilename(const std::string &path);

    /**
     * @brief getPath Utility function which returns the path from a passed absolute file path
     * @param path \link{std::string} containing the full file path to extract the path from
     * @return  Sucess: \link{std::string} containing the path\n Failure: Empty \link{std::string}
     */
    static std::string getPath(const std::string &path);

    /**
     * @brief getExtension Utility function which returns the file extension from a passed absolute file path
     * @param path \link{std::string} containing the full file path to extract the file extension from
     * @return  Sucess: \link{std::string} containing the extension\n Failure: Empty \link{std::string}
     */
    static std::string getExtension(const std::string &path);

    /**
     * @brief buildPath Assembles an absolute file path given path, filename, extension and optional suffix
     * @param path \link{std::string} containing the base path
     * @param fileName \link{std::string} containing the filename
     * @param extension \link{std::string} containing the file extension
     * @param suffix Optional \link{std::string} containing a suffix.\n Will be inserted between filename and extension, separated by an underscore
     * @return \link{std::string} containing the absolute file path
     */
    static std::string buildPath(const std::string &path,
                                 const std::string &fileName,
                                 const std::string &extension,
                                 const std::string &suffix = "");

private:
    /**
     * @brief examineDirectory Examines the contents of a directory and returns them as \link{std::vector}<\link{std::string}>
     * @param pathName \link{std::string} containing the directory to examine
     * @return \link{std::vector}<\link{std::string}> containing the folder contents
     */
    static std::vector<std::string> examineDirectory(const std::string &pathName);

    /**
     * @brief appendDescriptor Appends a descriptor to a given labelfile
     * @param labelFilePath \link{std::string} containing the path to the labelfile
     * @param labelFileName \link{std::string} containing the labelfiles filename
     * @param fileName \link{std::string} containing the descriptor filename
     * @param label Descriptor label
     * @return boolean value if the file was written or not
     */
    static bool appendDescriptor(const std::string &labelFilePath,
                                 const std::string &labelFileName,
                                 const std::string &fileName,
                                 const int label);
};


}

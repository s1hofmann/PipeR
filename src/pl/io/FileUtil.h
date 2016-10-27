#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QString>
#include <QDir>
#include <QTextStream>

#include "FileReader.h"
#include "FileWriter.h"

#include "../core/utils/progressbar.h"
#include "../core/utils/Range.h"
#include "../pipeline/globals.h"
#include "../exception/error.h"

namespace pl {


class FileUtil
{
public:
    FileUtil();

    virtual ~FileUtil();

    /**
     * @brief loadImages Returns an std::vector of cv::Mat objects containing all images in a given folder.
     * @param path Folder to load images from
     * @return std::vector<cv::Mat>
     */
    static std::vector<cv::Mat> loadImages(const std::string &path);

    /**
     * @brief loadImagesFromLabelFile Returns a std::pair of std::vector<cv::Mat> and std::vector<int> read from a labelfile
     * @param labelFile Labelfile to read data from
     * @return std::pair<std::vector<cv::Mat>, std::vector<int>>
     */
    static std::vector<std::pair<cv::Mat, int>> loadImagesFromLabelFile(const std::string &labelFile);

    /**
     * @brief getFiles Returns an std::vector of std::string objects containing all files in a given folder.
     * @param path Folder to get files from
     * @return std::vector<std::string>
     */
    static std::vector<std::string> getFiles(const std::string &path,
                                             const std::vector<std::string> &filters = std::vector<std::string>());

    /**
     * @brief getFilesFromLabelFile Returns a std::pair of std::vector<std::string> and std::vector<int>, holding filenames and corresponding labels read from a given labelfile
     * @param labelFile File to read data from
     * @return std::pair<std::vector<std::string>, std::vector<int>>
     */
    static std::vector<std::pair<std::__1::string, int> > getFilesFromLabelFile(const std::string &labelFile,
                                                                                       const unsigned int maxFiles = 0);

    /**
     * @brief saveImage Utility function to save a cv::Mat as image
     * @param image cv::Mat to save
     * @param outputPath std::string containing the output path
     * @param imageFileName std::string containing the filename
     * @return boolean value if file was written or not
     */
    static bool saveImage(const cv::Mat &image,
                          const std::string &outputPath,
                          const std::string &imageFileName,
                          const std::string &prefix = std::string());

    /**
     * @brief loadImage Utility function to load an image into a cv::Mat object
     * @param fileName std::string containing the absolute path to the file
     * @return Success: cv::Mat object containing the image\n Failure: Empty cv::Mat
     */
    static cv::Mat loadImage(const std::string &fileName,
                             const std::string &prefix = std::string());

    /**
     * @brief saveBinary Utility function to save a cv::Mat in binary format
     * @param data cv::Mat to save
     * @param outputPath std::string containing the output path
     * @param imageFileName std::string containing the filename
     * @return boolean value if file was written or not
     */
    static bool saveBinary(const cv::Mat &data,
                           const std::string &outputPath,
                           const std::string &fileName,
                           const std::string &prefix = std::string());

    static cv::Mat loadBinary(const std::string &inputPath,
                              const std::string &fileName);

    static cv::Mat loadBinary(const std::string &fileName);

    /**
     * @brief saveYML Utility function to save a cv::Mat in YML format
     * @param data cv::Mat to save
     * @param outputPath std::string containing the output path
     * @param imageFileName std::string containing the filename
     * @return boolean value if file was written or not
     */
    static bool saveYML(const cv::Mat &data,
                        const std::string &outputPath,
                        const std::string &fileName,
                        const std::string &prefix = std::string());

    /**
     * @brief saveDescriptorWithLabel Utility function which saves a descriptor in binary format and appends its label to a labelfile
     * @param descriptor cv::Mat to save
     * @param label Corresponding label
     * @param outputPath std::string containing the output path
     * @param descriptorFileName std::string containing the filename to save
     * @param labelFileName std::string containing the absolute path to the label file
     * @return boolean value if descriptor was written or not
     */
    static bool saveDescriptorWithLabel(const cv::Mat &descriptor,
                                        const int label,
                                        const std::string &outputPath,
                                        const std::string &descriptorFileName,
                                        const std::string &labelFileName,
                                        const std::string &prefix = std::string());

    /**
     * @brief saveDescriptor Utility function which saves a descriptor in binary format
     * @param descriptor cv::Mat to save
     * @param outputPath std::string containing the output path
     * @param fileName std::string containing the filename to save
     * @return boolean value if descriptor was written or not
     */
    static bool saveDescriptor(const cv::Mat &descriptor,
                               const std::string &outputPath,
                               const std::string &fileName,
                               const std::string &prefix = std::string());

    /**
     * @brief loadDescriptors Utility function which loads maxDescriptors from a given set of files
     * @param fileNames std::vector<std::string> containing the descriptor filenames
     * @param maxDescriptors Max descriptors to load
     * @param random Randomly load descriptors
     * @param seed Seed for PRNG, if -1 is passed, the current time will be used
     * @return cv::Mat containing all descriptors
     */
    static cv::Mat loadDescriptors(const std::string &descriptorDir,
                                   const std::string &labelFile,
                                   const int maxDescriptors,
                                   bool random = true);

    /**
     * @brief getFilename Utility function which returns the filename from a passed absolute file path
     * @param path std::stringfull file path to extract the filename from
     * @return  Sucess: std::string containing the filename\n Failure: Empty std::string
     */
    static std::string getFilename(const std::string &path);

    /**
     * @brief getPath Utility function which returns the path from a passed absolute file path
     * @param path std::string containing the full file path to extract the path from
     * @return  Sucess: std::string containing the path\n Failure: Empty std::string
     */
    static std::string getPath(const std::string &path);

    /**
     * @brief getExtension Utility function which returns the file extension from a passed absolute file path
     * @param path std::string containing the full file path to extract the file extension from
     * @return  Sucess: std::string containing the extension\n Failure: Empty std::string
     */
    static std::string getExtension(const std::string &path);

    /**
     * @brief buildPath Assembles an absolute file path given path, filename, extension and optional suffix
     * @param path std::string containing the base path
     * @param fileName std::string containing the filename
     * @param extension std::string containing the file extension
     * @param suffix Optional std::string containing a suffix.\n Will be inserted between filename and extension, separated by an underscore
     * @return std::string containing the absolute file path
     */
    static std::string buildPath(const std::string &path,
                                 const std::string &fileName,
                                 const std::string &extension,
                                 const std::string &suffix = "");

private:
    /**
     * @brief examineDirectory Examines the contents of a directory and returns them as \link{std::vector}<\link{std::string}>
     * @param pathName std::string containing the directory to examine
     * @return std::vector<std::string> containing the folder contents
     */
    static std::vector<std::string> examineDirectory(const std::string &pathName,
                                                     const std::vector<std::string> &filters = std::vector<std::string>());

    /**
     * @brief appendDescriptor Appends a descriptor to a given labelfile
     * @param labelFilePath std::string containing the path to the labelfile
     * @param labelFileName std::string containing the labelfiles filename
     * @param fileName std::string containing the descriptor filename
     * @param label Descriptor label
     * @return boolean value if the file was written or not
     */
    static bool appendDescriptor(const std::string &labelFileName,
                                 const std::string &outputPath,
                                 const std::string &fileName,
                                 const int label, const std::string &prefix);
};


}

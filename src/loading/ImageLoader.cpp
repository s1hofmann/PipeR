//
// Created by Simon Hofmann on 13.12.15.
//

#include "ImageLoader.h"

pl::ImageLoader::ImageLoader()
{

}


pl::ImageLoader::~ImageLoader()
{

}


std::vector<cv::Mat> pl::ImageLoader::loadImages(const std::string &path)
{
    std::vector<std::string> fileList = examineDirectory(path);
    std::vector<cv::Mat> imageList;

    ProgressBar<long> pb(fileList.size(), "Loading files...");

    for(size_t idx = 0; idx < fileList.size(); ++idx) {
        try {
            cv::Mat image = cv::imread(fileList[idx], CV_LOAD_IMAGE_UNCHANGED);
            if(!image.empty()) {
                imageList.push_back(image);
            }
            pb.update(idx);
        } catch (cv::Exception &e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
    }

    std::cout << std::endl << imageList.size() << " images loaded." << std::endl;

    return imageList;
}


std::vector<std::string> pl::ImageLoader::getFiles(const std::string &path)
{
}


std::pair<std::vector<std::string>, std::vector<int>> pl::ImageLoader::getFilesFromLabelFile(const std::string &labelFile)
{
    QFile(QString::fromStdString(labelFile));
}


std::pair<std::vector<cv::Mat>, std::vector<int>> pl::ImageLoader::loadImagesFromLabelFile(const std::string &labelFile)
{
    QFile(QString::fromStdString(labelFile));
}


std::vector<std::string> pl::ImageLoader::examineDirectory(const std::string &path)
{
    QDir dir(QString::fromStdString(path));
    std::vector<std::string> returnFiles;

    if(dir.exists()) {
        QFileInfoList fileList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);

        foreach(QFileInfo file, fileList) {
            QString absPath = file.absoluteFilePath();
            if(file.isDir()) {
                std::vector<std::string> dirEntries = examineDirectory(absPath.toStdString());
                returnFiles.insert(returnFiles.end(), dirEntries.begin(), dirEntries.end());
            } else {
                returnFiles.push_back(absPath.toStdString());
            }
        }

        return returnFiles;
    } else {
        std::cerr << "Directory does not exist, aborting." << std::endl;
        return std::vector<std::string>();
    }
}

#include "FileUtil.h"

namespace pl {


FileUtil::FileUtil()
{

}

FileUtil::~FileUtil()
{

}

std::vector<cv::Mat> FileUtil::loadImages(const std::string &path)
{
    std::vector<std::string> fileList = examineDirectory(path);
    std::vector<cv::Mat> imageList;

    ProgressBar<long> pb(fileList.size(), "Loading images...");

    for(size_t idx = 0; idx < fileList.size(); ++idx) {
        try {
            cv::Mat image = cv::imread(fileList[idx], CV_LOAD_IMAGE_UNCHANGED);
            if(!image.empty()) {
                imageList.push_back(image);
            }
            pb.update();
        } catch (cv::Exception &e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
    }

    std::cout << std::endl << imageList.size() << " images loaded." << std::endl;

    return imageList;
}


std::vector<std::string> FileUtil::getFiles(const std::string &path)
{
    std::vector<std::string> files = examineDirectory(path);
    ProgressBar<long> pb(files.size() - 1, "Fetching files...");
    for(size_t idx = 0; idx < files.size(); ++idx) {
        pb.update();
    }

    return files;
}


std::pair<std::vector<std::string>, std::vector<int>> FileUtil::getFilesFromLabelFile(const std::string &labelFile)
{
    QFile f(QString::fromStdString(labelFile));

    std::vector<std::string> path;
    std::vector<int> labels;

    if(f.exists()) {
        if (f.open(QIODevice::ReadOnly)) {
           QTextStream in(&f);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              QStringList parts = line.split(" ");
              path.push_back(parts[0].toStdString());
              labels.push_back(parts[1].toInt());
           }
           f.close();
        }
    } else {
        std::cerr << "Label file does not exist, aborting." << std::endl;
        exit(-1);
    }

    return std::make_pair(path, labels);
}


std::pair<std::vector<cv::Mat>, std::vector<int>> FileUtil::loadImagesFromLabelFile(const std::string &labelFile)
{
    std::pair<std::vector<std::string>, std::vector<int>> filesWithLabels = this->getFilesFromLabelFile(labelFile);

    try {
        std::vector<cv::Mat> loadedImages;
        std::vector<int> loadedLabels;

        for(size_t idx = 0; idx < filesWithLabels.first.size(); ++idx) {
            QFileInfo qf(QString::fromStdString(labelFile));
            QDir baseDir = qf.absoluteDir();
            QString imageFile(baseDir.absoluteFilePath(QString::fromStdString(filesWithLabels.first[idx])));
            cv::Mat image = cv::imread(imageFile.toStdString(), CV_LOAD_IMAGE_UNCHANGED);

            if(!image.empty()) {
                loadedImages.push_back(image);
                loadedLabels.push_back(filesWithLabels.second[idx]);
            }
        }

        return std::make_pair(loadedImages, loadedLabels);
    } catch (cv::Exception &e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
}

std::vector<std::string> FileUtil::examineDirectory(const std::string &pathName) const
{
    QDir dir(QString::fromStdString(pathName));
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


}

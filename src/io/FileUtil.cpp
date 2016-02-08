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

    FileReader<IMG> reader;

    ProgressBar<long> pb(fileList.size(), "Loading images...");

    for(size_t idx = 0; idx < fileList.size(); ++idx) {
        try {
            cv::Mat image = reader.read(fileList[idx]);
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


bool FileUtil::saveImage(const cv::Mat &image,
                         const std::string &outputPath,
                         const std::string &imageFileName)
{
    FileWriter<IMG> imageWriter;

    return imageWriter.write(image,
                             outputPath,
                             imageFileName);
}


cv::Mat FileUtil::loadImage(const std::string &fileName)
{
    FileReader<IMG> imageReader;

    return imageReader.read(fileName);
}


bool FileUtil::saveBinary(const cv::Mat &data,
                          const std::string &outputPath,
                          const std::string &fileName)
{
    FileWriter<BIN> binaryWriter;

    return binaryWriter.write(data,
                              outputPath,
                              fileName);
}


bool FileUtil::saveYML(const cv::Mat &data,
                       const std::string &outputPath,
                       const std::string &fileName)
{
    FileWriter<YML> ymlWriter;

    return ymlWriter.write(data,
                           outputPath,
                           fileName);
}


bool FileUtil::saveDescriptorWithLabel(const cv::Mat &descriptor,
                                       const int label,
                                       const std::string &outputPath,
                                       const std::string &descriptorFileName,
                                       const std::string &labelFileName)
{
    FileWriter<BIN> writer;

    if(!descriptor.empty()) {
        QDir outputDir(QString::fromStdString(outputPath));
        if(outputDir.exists()) {
            if(writer.write(descriptor, outputPath, descriptorFileName)) {
                if(appendDescriptor(outputPath,
                                    labelFileName,
                                    descriptorFileName,
                                    label)) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            error("Output directory doesn't exist, aborting.");
            return false;
        }
    } else {
        error("Empty output object given, aborting.");
        return false;
    }
}


bool FileUtil::saveDescriptor(const cv::Mat &descriptor,
                              const std::string &outputPath,
                              const std::string &fileName)
{
    FileWriter<BIN> writer;

    if(!descriptor.empty()) {
        QDir outputDir(QString::fromStdString(outputPath));
        if(outputDir.exists()) {
            if(writer.write(descriptor, outputPath, fileName)) {
                return true;
            } else {
                return false;
            }
        } else {
            error("Output directory doesn't exist, aborting.");
            return false;
        }
    } else {
        error("Empty output object given, aborting.");
        return false;
    }
}

std::string FileUtil::getFilename(const std::string &path)
{
    QFileInfo info(QString::fromStdString(path));

    if(info.exists()) {
        return info.completeBaseName().toStdString();
    } else {
        warning("File ", path , " doesn't exist!");
        return std::string();
    }
}

std::string FileUtil::getPath(const std::string &path)
{
    QFileInfo info(QString::fromStdString(path));

    if(info.exists()) {
        return info.absolutePath().toStdString();
    } else {
        warning("File ", path , " doesn't exist!");
        return std::string();
    }
}

std::string FileUtil::getExtension(const std::string &path)
{
    QFileInfo info(QString::fromStdString(path));

    if(info.exists()) {
        return info.completeSuffix().toStdString();
    } else {
        warning("File ", path , " doesn't exist!");
        return std::string();
    }
}

std::string FileUtil::buildPath(const std::string &path,
                                const std::string &fileName,
                                const std::string &extension,
                                const std::string &suffix)
{
    std::stringstream s;
    s << fileName << "_" << suffix << "." << extension;

    QFileInfo info(QDir(QString::fromStdString(path)), QString::fromStdString(s.str()));

    return info.absoluteFilePath().toStdString();
}

std::pair<std::vector<cv::Mat>, std::vector<int>> FileUtil::loadImagesFromLabelFile(const std::string &labelFile)
{
    FileReader<IMG> reader;
    std::pair<std::vector<std::string>, std::vector<int>> filesWithLabels = getFilesFromLabelFile(labelFile);

    try {
        std::vector<cv::Mat> loadedImages;
        std::vector<int> loadedLabels;

        for(size_t idx = 0; idx < filesWithLabels.first.size(); ++idx) {
            QFileInfo qf(QString::fromStdString(labelFile));
            QDir baseDir = qf.absoluteDir();
            QString imageFile(baseDir.absoluteFilePath(QString::fromStdString(filesWithLabels.first[idx])));
            cv::Mat image = reader.read(imageFile.toStdString());

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


std::vector<std::string> FileUtil::examineDirectory(const std::string &pathName)
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


bool FileUtil::appendDescriptor(const std::string &labelFilePath,
                                const std::string &labelFileName,
                                const std::string &fileName,
                                const int label)
{
    QDir outputDir(QString::fromStdString(labelFilePath));
    if(outputDir.exists()) {
        QFileInfo labelFileInfo(outputDir, QString::fromStdString(labelFileName));
        QFile fileHandler(labelFileInfo.absoluteFilePath());

        if(!fileHandler.exists()) {
            //If the file doesn't exist yet, it'll be created
            if(fileHandler.open(QIODevice::WriteOnly | QIODevice::Text)) {
                fileHandler.close();
            } else {
                error("Unable to create labelfile.");
                return false;
            }
        }

        if(!fileHandler.open(QIODevice::Append | QIODevice::Text)) {
            error("Unable to open labelfile.");
            return false;
        }

        QTextStream out(&fileHandler);
        out << QString::fromStdString(fileName) << " " << label << "\n";

        fileHandler.close();

        return true;
    } else {
        error("Output directory doesn't exist, aborting.");
        return false;
    }
}


}

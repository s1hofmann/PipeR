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

    for(size_t idx = 0; idx < fileList.size(); ++idx) {
        try {
            cv::Mat image = reader.read(fileList[idx]);
            if(!image.empty()) {
                imageList.push_back(image);
            }
        } catch (cv::Exception &e) {
            throw IOError(e.what(), currentMethod, currentLine);
        }
    }

    std::cout << std::endl << imageList.size() << " images loaded." << std::endl;

    return imageList;
}


std::vector<std::string> FileUtil::getFiles(const std::string &path,
                                            const std::vector<std::string> &filters)
{
    std::vector<std::string> files = examineDirectory(path, filters);
    return files;
}


std::vector<std::pair<std::string, int32_t>> FileUtil::getFilesFromLabelFile(const std::string &labelFile,
                                                                         const uint32_t maxFiles)
{
    QFile f(QString::fromStdString(labelFile));

    std::vector<std::pair<std::string, int32_t>> files;

    if(f.exists()) {
        if (f.open(QIODevice::ReadOnly)) {
           QTextStream in(&f);
           while(!in.atEnd() && (maxFiles <= 0 || (maxFiles > 0 && files.size() < maxFiles)))
           {
              QString line = in.readLine();
              QStringList parts = line.split(" ");
              if(parts.size() == 2) {
                  files.push_back(std::make_pair(parts[0].toStdString(), parts[1].toInt()));
              } else {
                  warning("Incompatible lable format. Skipping.");
                  continue;
              }
           }
           f.close();
        }
    } else {
        std::stringstream s;
        s << "Label file " << labelFile << " does not exist. Aborting." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    return files;
}


bool FileUtil::saveImage(const cv::Mat &image,
                         const std::string &outputPath,
                         const std::string &imageFileName,
                         const std::string &prefix)
{
    FileWriter<IMG> imageWriter;

    try {
        bool result = imageWriter.write(image,
                                        outputPath,
                                        imageFileName,
                                        prefix);

        return result;
    } catch(std::runtime_error) {
        throw;
    }
}


cv::Mat FileUtil::loadImage(const std::string &fileName,
                            const std::string &prefix)
{
    FileReader<IMG> imageReader;

    return imageReader.read(fileName,
                            prefix);
}


bool FileUtil::saveBinary(const cv::Mat &data,
                          const std::string &outputPath,
                          const std::string &fileName,
                          const std::string &prefix)
{
    FileWriter<BIN> binaryWriter;

    return binaryWriter.write(data,
                              outputPath,
                              fileName,
                              prefix);
}


cv::Mat FileUtil::loadBinary(const std::string &inputPath,
                             const std::string &fileName)
{
    FileReader<BIN> binaryReader;

    QDir inDir(QString::fromStdString(inputPath));
    QFileInfo info(inDir, QString::fromStdString(fileName));

    try {
        return binaryReader.read(info.absoluteFilePath().toStdString());
    } catch(IOError) {
        throw;
    }
}


cv::Mat FileUtil::loadBinary(const std::string &fileName)
{
    FileReader<BIN> binaryReader;

    try {
        return binaryReader.read(fileName);
    } catch(IOError) {
        throw;
    }
}


bool FileUtil::saveYML(const cv::Mat &data,
                       const std::string &outputPath,
                       const std::string &fileName, const std::string &prefix)
{
    FileWriter<YML> ymlWriter;

    try {
        return ymlWriter.write(data,
                               outputPath,
                               fileName);
    } catch(IOError) {
        throw;
    }
}


bool FileUtil::saveDescriptorWithLabel(const cv::Mat &descriptor,
                                       const int32_t label,
                                       const std::string &outputPath,
                                       const std::string &descriptorFileName,
                                       const std::string &labelFileName, const std::string &prefix)
{
    FileWriter<BIN> writer;

    if(!descriptor.empty()) {
        QDir outputDir(QString::fromStdString(outputPath));
        if(outputDir.exists()) {
            if(writer.write(descriptor, outputPath, descriptorFileName, prefix)) {
                if(appendDescriptor(labelFileName,
                                    outputPath,
                                    descriptorFileName,
                                    label,
                                    prefix)) {
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
                              const std::string &fileName,
                              const std::string &prefix)
{
    FileWriter<BIN> writer;

    if(!descriptor.empty()) {
        QDir outputDir(QString::fromStdString(outputPath));
        if(outputDir.exists()) {
            if(writer.write(descriptor, outputPath, fileName, prefix)) {
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

cv::Mat FileUtil::loadDescriptors(const std::string &descriptorDir,
                                  const std::string &labelFile,
                                  const uint32_t maxDescriptors,
                                  bool random)
{
    std::vector<std::pair<std::string, int32_t>> filesWithLabels = getFilesFromLabelFile(labelFile);

    int32_t maxDescriptorsPerFile = maxDescriptors / filesWithLabels.size();

    cv::Mat allDescriptors;
    int32_t idx = 0;

    while((allDescriptors.rows < maxDescriptors || maxDescriptors <= 0) && idx < filesWithLabels.size()) {
        cv::Mat desc = loadBinary(filesWithLabels[idx].first);

        int32_t rows;
        if(maxDescriptors <= 0) {
            rows = desc.rows;
        } else {
            rows = std::min(desc.rows, maxDescriptorsPerFile);
        }

        std::vector<int32_t> indices;
        allDescriptors.reserve(rows);
        if(random) {
            indices = Range<int32_t>::random(0, rows);
        } else {
            indices = Range<int32_t>::unique(0, rows);
        }

        for(size_t i = 0; i < indices.size(); ++i) {
            if(desc.cols == allDescriptors.cols || allDescriptors.empty()) {
                allDescriptors.push_back(desc.row(indices[i]));
            }
        }
        ++idx;
    }

    return allDescriptors;
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

bool FileUtil::isFile(const std::string &path)
{
    QFileInfo fi(QString::fromStdString(path));

    return fi.isFile();
}

bool FileUtil::isDir(const std::string &path)
{
    QFileInfo fi(QString::fromStdString(path));

    return fi.isDir();
}

std::vector<std::pair<cv::Mat, int32_t>> FileUtil::loadImagesFromLabelFile(const std::string &labelFile)
{
    FileReader<IMG> reader;
    std::vector<std::pair<std::string, int32_t>> filesWithLabels = getFilesFromLabelFile(labelFile);

    try {
        std::vector<std::pair<cv::Mat, int32_t>> loadedFiles;

        for(size_t idx = 0; idx < filesWithLabels.size(); ++idx) {
            QFileInfo qf(QString::fromStdString(labelFile));
            QDir baseDir = qf.absoluteDir();
            QString imageFile(baseDir.absoluteFilePath(QString::fromStdString(filesWithLabels[idx].first)));
            cv::Mat image = reader.read(imageFile.toStdString());

            if(!image.empty()) {
                loadedFiles.push_back(std::make_pair(image, filesWithLabels[idx].second));
            }
        }

        return loadedFiles;
    } catch (cv::Exception &e) {
        throw IOError(e.what(), currentMethod, currentLine);
    }
}


std::vector<std::string> FileUtil::examineDirectory(const std::string &pathName,
                                                    const std::vector<std::string> &filters)
{
    QDir dir(QString::fromStdString(pathName));
    std::vector<std::string> returnFiles;

    QStringList filter;

    for(size_t idx = 0; idx < filters.size(); ++idx) {
        filter << QString::fromStdString(filters[idx]);
    }

    dir.setNameFilters(filter);

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
        std::stringstream s;
        s << "Directory " << pathName << " does not exist. Aborting" << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
}


bool FileUtil::appendDescriptor(const std::string &labelFileName,
                                const std::string &outputPath,
                                const std::string &fileName,
                                const int32_t label,
                                const std::string &prefix)
{
    QDir d(QString::fromStdString(outputPath));
    std::stringstream s;
    if(!prefix.empty()) {
        s << prefix << "_";
    }
    s << fileName;
    QString absFile = d.absoluteFilePath(QString::fromStdString(s.str()));
    QFileInfo labelFileInfo(QString::fromStdString(labelFileName));
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
    out << absFile << " " << label << "\n";

    fileHandler.close();

    return true;
}


}

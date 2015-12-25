#include "yml.h"


namespace pl {


YML::YML()
    : IOImpl()
{

}


YML::~YML()
{

}


bool YML::write(const cv::Mat &output,
                const std::string &outPath,
                const std::string &fileName) const
{
    if(outPath.empty()) {
        std::cerr << "No output path given, aborting." << std::endl;
        return false;
    }
    if(fileName.empty()) {
        std::cerr << "No filename given, aborting." << std::endl;
        return false;
    }

    QDir d(QString::fromStdString(outPath));
    QString absFile = d.absoluteFilePath(QString::fromStdString(fileName));

    try {
        cv::FileStorage fs(absFile.toStdString(), cv::FileStorage::WRITE);
        fs << "descriptors" << output;
        fs.release();
        return true;
    } catch (cv::Exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}


cv::Mat YML::read(const std::string &input) const
{
    if(input.empty()) {
        std::cerr << "No filename given, aborting." << std::endl;
        return cv::Mat();
    }

    cv::Mat descr;
    cv::FileStorage fs(input, cv::FileStorage::READ);
    fs["descriptors"] >> descr;
    fs.release();

    return descr;
}


}

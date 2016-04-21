//
// Created by Simon Hofmann on 25.12.15.
//

#include "yml.h"


namespace pl {


YML::YML()
    : IOImpl()
{

}


YML::~YML()
{

}


unsigned long YML::write(const cv::Mat &output,
                         const std::string &outPath,
                         const std::string &fileName) const
{
    if(output.empty()) {
        std::stringstream s;
        s << "Empty output object given." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
    if(outPath.empty()) {
        std::stringstream s;
        s << "Empty output object given." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
    if(fileName.empty()) {
        std::stringstream s;
        s << "No filename given." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    QDir d(QString::fromStdString(outPath));
    QString absFile = d.absoluteFilePath(QString::fromStdString(fileName));

    try {
        cv::FileStorage fs(absFile.toStdString(), cv::FileStorage::WRITE);
        fs << "descriptors" << output;
        fs.release();
        return output.rows * output.cols * output.channels();
    } catch (cv::Exception &e) {
        throw;
    }
}


cv::Mat YML::read(const std::string &input) const
{
    if(input.empty()) {
        std::stringstream s;
        s << "No filename given." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    cv::Mat descr;
    cv::FileStorage fs(input, cv::FileStorage::READ);
    fs["descriptors"] >> descr;
    fs.release();

    return descr;
}


}

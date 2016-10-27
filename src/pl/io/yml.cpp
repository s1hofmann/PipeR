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
                         const std::string &fileName,
                         const std::string &prefix) const
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
    std::stringstream s;
    if(!prefix.empty()) {
        s << prefix << "_";
    }
    s << fileName;
    QString absFile = d.absoluteFilePath(QString::fromStdString(s.str()));

    try {
        cv::FileStorage fs(absFile.toStdString(), cv::FileStorage::WRITE);
        fs << "descriptors" << output;
        fs.release();
        return output.rows * output.cols * output.channels();
    } catch (cv::Exception &e) {
        throw;
    }
}


cv::Mat YML::read(const std::string &input, const std::string &prefix) const
{
    if(input.empty()) {
        std::stringstream s;
        s << "No filename given." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    cv::Mat descr;
    std::stringstream s;
    if(!prefix.empty()) {
        s << prefix << "_";
    }
    s << input;
    cv::FileStorage fs(s.str(), cv::FileStorage::READ);
    fs["descriptors"] >> descr;
    fs.release();

    return descr;
}


}

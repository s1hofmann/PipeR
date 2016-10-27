//
// Created by Simon Hofmann on 25.12.15.
//

#include "img.h"


namespace pl {


IMG::IMG()
    :
        IOImpl()
{

}


IMG::~IMG()
{

}


unsigned long IMG::write(const cv::Mat &output,
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
        s << "No output path given." << std::endl;
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

    std::vector<int> parameters;

    if(cv::imwrite(absFile.toStdString(), output)) {
        return output.rows * output.cols * output.channels();
    } else {
        std::stringstream s;
        s << "Failed to write " << absFile.toStdString() << "." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
}


cv::Mat IMG::read(const std::string &input, const std::string &prefix) const
{
    if(input.empty()) {
        std::stringstream s;
        s << "No filename given." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    std::stringstream s;
    if(!prefix.empty()) {
        s << prefix << "_";
    }
    s << input;
    cv::Mat img = cv::imread(s.str(), CV_LOAD_IMAGE_UNCHANGED);

    if(img.empty()) {
        warning(input, "is and empty image.");
    }

    return img;
}


}

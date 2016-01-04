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
                const std::string &fileName) const
{
    if(output.empty()) {
        throw new std::invalid_argument("Empty output object given.\n");
    }
    if(outPath.empty()) {
        throw new std::invalid_argument("No output path given.\n");
    }
    if(fileName.empty()) {
        throw new std::invalid_argument("No filename given.\n");
    }

    QDir d(QString::fromStdString(outPath));
    QString absFile = d.absoluteFilePath(QString::fromStdString(fileName));

    std::vector<int> parameters;

    if(cv::imwrite(absFile.toStdString(), output)) {
        return output.rows * output.cols * output.channels();
    } else {
        std::stringstream s;
        s << "Failed to write " << absFile.toStdString() << "." << std::endl;
        throw new std::runtime_error(s.str());
    }
}


cv::Mat IMG::read(const std::string &input) const
{
    if(input.empty()) {
        throw new std::invalid_argument("No filename given.\n");
    }

    cv::Mat img = cv::imread(input, CV_LOAD_IMAGE_UNCHANGED);

    if(img.empty()) {
        warning(input, "is and empty image.");
    }

    return img;
}


}

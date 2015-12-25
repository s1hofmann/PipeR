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


bool IMG::write(const cv::Mat &output,
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

    std::vector<int> parameters;

    if(!cv::imwrite(absFile.toStdString(), output)) {
        std::cerr << "Failed to write " << absFile.toStdString() << "." << std::endl;
        return false;
    }

    return true;
}


cv::Mat IMG::read(const std::string &input) const
{
    if(input.empty()) {
        std::cerr << "No filename given, aborting." << std::endl;
        return cv::Mat();
    }

    return cv::imread(input, CV_LOAD_IMAGE_UNCHANGED);
}


}

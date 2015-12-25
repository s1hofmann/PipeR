#include "png.h"


namespace pl {


PNG::PNG()
    :
        IOImpl()
{

}


PNG::~PNG()
{

}


bool PNG::write(const cv::Mat &output,
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

    // png compression level
    std::vector<int> parameters;
#if CV_MAJOR_VERSION >= 3
    parameters.push_back(cv::IMWRITE_PNG_COMPRESSION);
#else
    parameters.push_back(CV_IMWRITE_PNG_COMPRESSION);
#endif
    parameters.push_back(9); // highest compression

    if(!cv::imwrite(absFile.toStdString(), output, parameters) ){
        std::cerr << "Failed to write " << absFile.toStdString() << "." << std::endl;
        return false;
    }

    return true;
}


cv::Mat PNG::read(const std::string &input) const
{
    if(input.empty()) {
        std::cerr << "No filename given, aborting." << std::endl;
        return cv::Mat();
    }

    return cv::imread(input, CV_LOAD_IMAGE_UNCHANGED);
}


}

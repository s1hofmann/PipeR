//
// Created by Simon Hofmann on 25.12.15.
//

#include "csv.h"


namespace pl {


CSV::CSV()
    :
        IOImpl()
{

}


CSV::~CSV()
{

}


bool CSV::write(const cv::Mat &output,
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

    QFile file(absFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
        std::cerr << "Unable to open file " << absFile.toStdString() << std::endl;
        return false;
    }

    QTextStream file_stream(&file);
    for(int y = 0; y < output.rows; y++ ) {
        for(int x = 0; x < output.cols; x++ ) {
            if(output.type() == CV_32FC1)
                file_stream << (float)output.at<float>(y,x);
            else if(output.type() == CV_64FC1 )
                file_stream << (double)output.at<double>(y,x);
            else if(output.type() == CV_32SC1 )
                file_stream << (int)output.at<int>(y,x);
            else if(output.type() == CV_8UC1 )
                file_stream << (uchar)output.at<uchar>(y,x);
            else
                std::cerr << "Format not supported." << std::endl;
            if(x != output.cols - 1) {
                file_stream << ",";
            }
        }
        file_stream << "\n";
    }
    file.close();

    return true;
}


cv::Mat CSV::read(const std::string &input) const
{
    if(input.empty()) {
        std::cerr << "No filename given, aborting." << std::endl;
        return cv::Mat();
    }

    QFile file(QString::fromStdString(input));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       return cv::Mat();
    }

    QTextStream file_stream(&file);

    int rows = 0;
    int cols = 0;
    std::vector<float> vals;
    QString line;
    while((line = file_stream.readLine()) != QString::null) {
       QStringList val_str = line.split(',', QString::SkipEmptyParts);

       int col = 0;
       foreach(QString v, val_str){
           bool ok;
           vals.push_back(v.toFloat(&ok));
           assert(ok);
           col++;
       }
       if((vals.size() % col) != 0) {
           std::cerr << "Error, wrong dimension!" << std::endl;
           std::cerr << "Is: " << vals.size() << " Should be: " << col << std::endl;
       }
       if(cols != 0 && cols != col) {
           std::cerr << "Error, columns missaligned." << std::endl;
       }
       cols = col;
       rows++;
    }
    cv::Mat descr = cv::Mat1f(vals);
    descr = descr.reshape(0,rows);
    file.close();

    return descr;
}


}

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


unsigned long CSV::write(const cv::Mat &output,
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

    QFile file(absFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
        std::stringstream s;
        s << "Unable to open file " << absFile.toStdString() << "." << std::endl;
        throw new std::runtime_error(s.str());
    }

    QTextStream file_stream(&file);

    unsigned long count = 0;

    for(int y = 0; y < output.rows; y++ ) {
        for(int x = 0; x < output.cols; x++ ) {
            if(output.type() == CV_32FC1) {
                file_stream << (float)output.at<float>(y,x);
                ++count;
            } else if(output.type() == CV_64FC1 ) {
                file_stream << (double)output.at<double>(y,x);
                ++count;
            } else if(output.type() == CV_32SC1 ) {
                file_stream << (int)output.at<int>(y,x);
                ++count;
            } else if(output.type() == CV_8UC1 ) {
                file_stream << (uchar)output.at<uchar>(y,x);
                ++count;
            } else {
                throw new std::runtime_error("Format not supported.\n");
            }
            if(x != output.cols - 1) {
                file_stream << ",";
            }
        }
        file_stream << "\n";
    }
    file.close();

    return count;
}


cv::Mat CSV::read(const std::string &input) const
{
    if(input.empty()) {
        std::invalid_argument("No filename given.\n");
    }

    QFile file(QString::fromStdString(input));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::stringstream s;
        s << "Unable to open file " << input << "." << std::endl;
        throw new std::runtime_error(s.str());
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
           if(!ok) {
               throw new std::runtime_error("Error while parsing CSV data.\n");
           }
           col++;
       }
       if((vals.size() % col) != 0) {
           std::stringstream s;
           s << "Size error!" << std::endl << "Is: " << vals.size() << " Should be: " << col << std::endl;
           throw new std::runtime_error(s.str());
       }
       if(cols != 0 && cols != col) {
           throw new std::runtime_error("Size error! Data missaligned.\n");
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

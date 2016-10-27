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

    QFile file(absFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
        std::stringstream s;
        s << "Unable to open file " << absFile.toStdString() << "." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
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
                std::stringstream s;
                s << "Format not supported." << std::endl;
                throw IOError(s.str(), currentMethod, currentLine);
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


cv::Mat CSV::read(const std::string &input, const std::string &prefix) const
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
    QFile file(QString::fromStdString(s.str()));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::stringstream s;
        s << "Unable to open file " << input << "." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
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
               std::stringstream s;
               s << "Error while parsing CSV data." << std::endl;
               throw IOError(s.str(), currentMethod, currentLine);
           }
           col++;
       }
       if((vals.size() % col) != 0) {
           std::stringstream s;
           s << "Size error!" << std::endl << "Is: " << vals.size() << " Should be: " << col << std::endl;
           throw IOError(s.str(), currentMethod, currentLine);
       }
       if(cols != 0 && cols != col) {
           std::stringstream s;
           s << "Size error! Data missaligned." << std::endl;
           throw IOError(s.str(), currentMethod, currentLine);
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

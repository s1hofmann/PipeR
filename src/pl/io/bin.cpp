//
// Created by Simon Hofmann on 25.12.15.
//

#include "bin.h"


namespace pl {


BIN::BIN()
    :
        IOImpl()
{

}


BIN::~BIN()
{

}


unsigned long BIN::write(const cv::Mat &output,
                         const std::string &outPath,
                         const std::string &fileName) const
{
    if(output.empty()) {
        std::stringstream s;
        s << "Output object empty." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
    if(outPath.empty()) {
        std::stringstream s;
        s << "Output path missing." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
    if(fileName.empty()) {
        std::stringstream s;
        s << "File name missing." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    if(output.channels() != 1) {
        std::stringstream s;
        s << "Output data has multiple channels, currently not supported." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
    if(!output.isContinuous()) {
        std::stringstream s;
        s << "Output data is not continous." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    QDir d(QString::fromStdString(outPath));
    QString absFile = d.absoluteFilePath(QString::fromStdString(fileName));
    QFile file(absFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::QIODevice::Unbuffered)) {
        std::stringstream s;
        s << "Unable to open file " << absFile.toStdString() << "." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    int chans = output.channels();

    int dataSize;

    switch(output.depth()) {
    case CV_8U:
        file.putChar('u');
        dataSize = sizeof(char);
        break;
    case CV_8S:
        file.putChar('c');
        dataSize = sizeof(char);
        break;
    case CV_16U:
        file.putChar('w');
        dataSize = sizeof(short);
        break;
    case CV_16S:
        file.putChar('s');
        dataSize = sizeof(short);
        break;
    case CV_32S:
        file.putChar('i');
        dataSize = sizeof(int);
        break;
    case CV_32F:
        file.putChar('f');
        dataSize = sizeof(float);
        break;
    case CV_64F:
        file.putChar('d');
        dataSize = sizeof(double);
        break;
    }

    file.write((char *)&output.rows, sizeof(int));
    file.write((char *)&output.cols, sizeof(int));
    file.write((char *)&chans, sizeof(int));
    file.write((char*)output.data,
               dataSize*output.rows*output.cols);
    file.close();

    return dataSize*output.rows*output.cols;
}


cv::Mat BIN::read(const std::string &input) const
{
    if(input.empty()) {
        std::stringstream s;
        s << "No filename given." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }
    QFile file(QString::fromStdString(input));
    if(!file.open(QIODevice::ReadOnly | QIODevice::QIODevice::Unbuffered)) {
        std::stringstream s;
        s << "Unable to open file " << input << "." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    char dtype;
    file.getChar(&dtype);
    int rows, cols, chans;
    file.read((char *)&rows, sizeof(int));
    file.read((char *)&cols, sizeof(int));
    file.read((char *)&chans, sizeof(int));
    if(chans != 1) {
        std::stringstream s;
        s << "Wrong channel size." << std::endl;
        throw IOError(s.str(), currentMethod, currentLine);
    }

    int dataSize;

    cv::Mat descr;

    switch(dtype) {
    case 'u':
        descr.create(rows, cols, CV_8UC1);
        dataSize = sizeof(char);
        break;
    case 'c':
        descr.create(rows, cols, CV_8SC1);
        dataSize = sizeof(char);
        break;
    case 'w':
        descr.create(rows, cols, CV_16UC1);
        dataSize = sizeof(short);
        break;
    case 's':
        descr.create(rows, cols, CV_16SC1);
        dataSize = sizeof(short);
        break;
    case 'i':
        descr.create(rows, cols, CV_32SC1);
        dataSize = sizeof(int);
        break;
    case 'f':
        descr.create(rows, cols, CV_32FC1);
        dataSize = sizeof(float);
        break;
    case 'd':
        descr.create(rows, cols, CV_64FC1);
        dataSize = sizeof(double);
        break;
    }
    file.read((char*)descr.data, dataSize*descr.rows*descr.cols);
    file.close();

    return descr;
}


}

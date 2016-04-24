#pragma once

#include "BaseLogger.h"

namespace pl {


class FileLogger : public BaseLogger
{
public:
    FileLogger(const std::string &file);

    virtual ~FileLogger();

    template <typename ... T>
    void inform(T ... information) {
        if(!mValidStream) {
            std::cerr << "Unable to write to log file." << std::endl;
        } else {
            mFileStream << i(information ...);
            mFileStream.flush();
        }
    }

    template <typename ... T>
    void debug(T ... msg) {
        if(!mValidStream) {
            std::cerr << "Unable to write to log file." << std::endl;
        } else {
            mFileStream << d(msg ...);
            mFileStream.flush();
        }
    }

    template <typename ... T>
    void warn(T ... warning) {
        if(!mValidStream) {
            std::cerr << "Unable to write to log file." << std::endl;
        } else {
            mFileStream << w(warning ...);
            mFileStream.flush();
        }
    }

    template <typename ... T>
    void report(T ... err) {
        if(!mValidStream) {
            std::cerr << "Unable to write to log file." << std::endl;
        } else {
            mFileStream << e(err ...);
            mFileStream.flush();
        }
    }

    bool validStream() const {
        return mValidStream;
    }

    void setValidStream(bool validStream) {
        mValidStream = validStream;
    }

private:
    std::ofstream mFileStream;
    bool mValidStream;
};


}

#include "FileLogger.h"

namespace pl {


FileLogger::FileLogger(const std::string &file)
    :
      BaseLogger()
{
    mFileStream = std::ofstream(file, std::ofstream::app);
    mValidStream = mFileStream.is_open();
}

FileLogger::~FileLogger() {
    mFileStream.close();
}


}

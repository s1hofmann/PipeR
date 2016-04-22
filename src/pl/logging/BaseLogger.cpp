#include "BaseLogger.h"

namespace pl {


BaseLogger::BaseLogger() {
    mStream.clear();
}

BaseLogger::~BaseLogger() {
}

std::string BaseLogger::timestamp()
{
    std::stringstream s;
    std::time_t currentTime = std::time(nullptr);
    s << std::put_time(std::localtime(&currentTime), "%R-%D ");

    return s.str();
}


}

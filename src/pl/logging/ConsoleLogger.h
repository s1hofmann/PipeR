#pragma once

#include "BaseLogger.h"

namespace pl {


class ConsoleLogger : public BaseLogger
{
public:
    ConsoleLogger();

    virtual ~ConsoleLogger();

    template <typename ... T>
    void inform(T ... information) {
        std::cout << i(information ...);
    }

    template <typename ... T>
    void debug(T ... msg) {
        std::cout << d(msg ...);
    }

    template <typename ... T>
    void warn(T ... warning) {
        std::cout << w(warning ...);
    }

    template <typename ... T>
    void report(T ... error) {
        std::cout << e(error ...);
    }

private:
    std::ofstream mFileStream;
};


}

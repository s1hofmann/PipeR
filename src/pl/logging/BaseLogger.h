#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>

namespace pl {

class BaseLogger
{
protected:
    template <typename T>
    void write(T msg) {
        mStream << msg << std::endl;
    }

    template <typename T, typename ... O>
    void write(T msg, O ... others) {
        mStream << msg << " ";
        write(others ...);
    }

    template <typename ... T>
    std::string i(T ... msg) {
        mStream << timestamp() << "INFO ";
        write(msg ...);

        return mStream.str();
    }

    template <typename ... T>
    std::string w(T ... msg) {
        mStream << timestamp() << "WARNING ";
        write(msg ...);

        return mStream.str();
    }

    template <typename ... T>
    std::string e(T ... msg) {
        mStream << timestamp() << "ERROR ";
        write(msg ...);

        return mStream.str();
    }

    template <typename ... T>
    std::string d(T ... msg) {
        mStream << timestamp() << std::string("DEBUG ");
        write(msg ...);

        return mStream.str();
    }

    BaseLogger();

    virtual ~BaseLogger();

private:
    std::string timestamp();

    std::stringstream mStream;
};

}

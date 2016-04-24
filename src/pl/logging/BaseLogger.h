#pragma once

#include <vector>
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
    void write(std::stringstream &s, T msg) {
        s << msg << std::endl;
    }

    template <typename T>
    void write(std::stringstream &s, std::vector<T> msg) {
        s << vec2string(msg) << std::endl;
    }

    template <typename T, typename ... O>
    void write(std::stringstream &s, T msg, O ... others) {
        s << msg << " ";
        write(s, others ...);
    }

    template <typename T, typename ... O>
    void write(std::stringstream &s, std::vector<T> msg, O ... others) {
        s << vec2string(msg) << " ";
        write(s, others ...);
    }

    template <typename ... T>
    std::string i(T ... msg) {
        std::stringstream s;
        s << timestamp() << "INFO ";
        write(s, msg ...);

        return s.str();
    }

    template <typename ... T>
    std::string w(T ... msg) {
        std::stringstream s;
        s << timestamp() << "WARNING ";
        write(s, msg ...);

        return s.str();
    }

    template <typename ... T>
    std::string e(T ... msg) {
        std::stringstream s;
        s << timestamp() << "ERROR ";
        write(s, msg ...);

        return s.str();
    }

    template <typename ... T>
    std::string d(T ... msg) {
        std::stringstream s;
        s << timestamp() << std::string("DEBUG ");
        write(s, msg ...);

        return s.str();
    }

    BaseLogger();

    virtual ~BaseLogger();

private:
    std::string timestamp();

    template <typename T>
    std::string vec2string(std::vector<T> msg) {
        std::stringstream s;
        s << "[";

        if(msg.size() > 10) {
            for(size_t idx = 0; idx < 5; ++idx) {
                s << msg[idx] << ", ";
            }

            s << "..., ";

            for(size_t idx = msg.size() - 5; idx < msg.size(); ++idx) {
                if(idx < msg.size() - 1) {
                    s << msg[idx] << ", ";
                } else {
                    s << msg[idx];
                }
            }
        } else if(msg.size() > 0 && msg.size() < 10) {
            for(size_t idx = 0; idx < msg.size(); ++idx) {
                if(idx < msg.size() - 1) {
                    s << msg[idx] << ", ";
                } else {
                    s << msg[idx];
                }
            }
        }

        s << "]";

        return s.str();
    }

    std::stringstream mStream;
};

}

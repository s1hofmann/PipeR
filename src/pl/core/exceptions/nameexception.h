#pragma once

#include <stdexcept>

namespace pl {


class NameException : public std::runtime_error
{
public:
    explicit NameException(const std::string &what_arg);
    explicit NameException(const char* what_arg);

    // exception interface
    virtual const char *what() const;
};


}


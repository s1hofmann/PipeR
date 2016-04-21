#include "nameexception.h"
#include <string>
#include <sstream>

namespace pl {


NameException::NameException(const std::string &what_arg)
{
    std::stringstream s;
    s << "Name '" << what_arg << "' already in use.";
    this->_M_msg = s.str();
}

NameException::NameException(const char *what_arg)
{
    std::stringstream s;
    s << "Name '" << std::string(what_arg) << "' already in use.";
    this->_M_msg = s.str();
}


const char* NameException::what() const
{
}


}


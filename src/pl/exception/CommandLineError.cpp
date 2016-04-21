#include "CommandLineError.h"

namespace pl {


CommandLineError::CommandLineError(const std::string &msg,
                                   const std::string &where,
                                   const int line)
    :
        BaseError(msg, where, line)
{
}


}

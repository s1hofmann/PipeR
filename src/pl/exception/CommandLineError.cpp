#include "CommandLineError.h"

namespace pl {


CommandLineError::CommandLineError(const std::string &msg,
                                   const std::string &where,
                                   const int32_t line)
    :
        BaseError("CommandLineError", msg, where, line)
{
}


}

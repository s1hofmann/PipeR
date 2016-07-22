#include "PreProcessError.h"


namespace pl {

PreProcessError::PreProcessError(const std::string &msg, const std::string &where, const int line)
    :
        BaseError(msg, where, line)
{
}

}

#include "PostProcessError.h"


namespace pl {

PostProcessError::PostProcessError(const std::string &msg, const std::string &where, const int line)
    :
        BaseError(msg, where, line)
{
}

}

#include "EncodingError.h"

namespace pl {

EncodingError::EncodingError(const std::string &msg, const std::string &where, const int line)
    :
        BaseError(msg, where, line)
{
}

}

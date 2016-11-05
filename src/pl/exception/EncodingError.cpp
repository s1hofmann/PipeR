#include "EncodingError.h"

namespace pl {

EncodingError::EncodingError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError(msg, where, line)
{
}

}

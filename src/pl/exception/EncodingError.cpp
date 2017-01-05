#include "EncodingError.h"

namespace pl {

EncodingError::EncodingError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError("EncodingError", msg, where, line)
{
}

}

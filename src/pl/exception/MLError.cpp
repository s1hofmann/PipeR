#include "MLError.h"


namespace pl {

MLError::MLError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError("MLError", msg, where, line)
{
}

}

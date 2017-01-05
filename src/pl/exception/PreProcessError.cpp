#include "PreProcessError.h"


namespace pl {

PreProcessError::PreProcessError(const std::string &msg, const std::string &where, const int32_t line)
    :
        BaseError("PreProcessingError", msg, where, line)
{
}

}

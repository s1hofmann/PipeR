#include "MLError.h"


namespace pl {

MLError::MLError(const std::string &msg, const std::string &where, const int line)
    :
        BaseError(msg, where, line)
{
}

}

#include "DataException.h"


namespace pl {


DataException::DataException(const std::string &what_arg)
    :
        std::runtime_error(what_arg)
{
}


}

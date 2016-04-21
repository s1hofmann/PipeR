#include "DimensionalityReductionError.h"

namespace pl {

DimensionalityReductionError::DimensionalityReductionError(const std::string &msg, const std::string &where, const int line)
    :
        Error(msg, where, line)
{
}

std::string DimensionalityReductionError::getMsg(const std::string &msg,
                                                 const std::string &where,
                                                 const int line) const
{
    std::stringstream s;
    if(!where.empty()) {
        s << "(Dimensionality reduction error in " << where << ", line " << line << ") ";
    }
    s << msg << std::endl;

    return s.str();
}

}

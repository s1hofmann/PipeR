#pragma once

#include "../../pl/pipeline/PipeLine.h"
#include "../../pl/exception/error.h"
#include "../../pl/core/utils/scalespace.h"
#include "../../pl/logging/logging.h"
#include "../../pl/exception/error.h"
#include <cstdlib>


class OptimizationProcessor
{
public:
    OptimizationProcessor(int argc, char *argv[]);

    int run();

    enum ReturnValues {
        RETURN_SUCCESS,
        RETURN_CLASSIFICATION_ERROR,
        RETURN_CLUSTERING_ERROR,
        RETURN_COMMANDLINE_ERROR,
        RETURN_DIM_ERROR,
        RETURN_ENCODING_ERROR,
        RETURN_FEATURE_EX_ERROR,
        RETURN_IO_ERROR,
        RETURN_ML_ERROR,
        RETURN_OPENCV_ERROR,
        RETURN_ERROR
    };

private:
    std::unordered_map<std::string, std::string> mArguments;
};

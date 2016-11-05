#pragma once

#include "../../pl/pipeline/PipeLine.h"
#include "../../pl/exception/error.h"
#include "../../pl/core/utils/scalespace.h"
#include "../../pl/logging/logging.h"
#include "foldersummary.h"
#include "filesummary.h"
#include <cstdlib>


class MomProcessor
{
public:
    MomProcessor(int32_t argc, char *argv[]);

    int32_t run();

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
        RETURN_OPENCV_ERROR
    };

private:
    std::unordered_map<std::string, std::string> mArguments;
    int32_t mWindowSize;
    int32_t mStepSize;
    double mThreshold;
    int32_t mOctaves;
    int32_t mStages;
};

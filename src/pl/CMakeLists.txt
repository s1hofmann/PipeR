# Pipeline options
option (DIMENSIONALITY_REDUCTION
        "Enable dimensionality reduction?" ON)

option (ENCODING
        "Enable encoding?" ON)

option (PREPROCESSING
        "Enable preprocessing?" ON)

option (POSTPROCESSING
        "Enable postprocessing?" ON)

option (MASKS
        "Enable masks?" ON)

include_directories ("core/clustering")
add_subdirectory(core/clustering)
set (EXTRA_LIBS ${EXTRA_LIBS} clustering_core)

include_directories ("core/utils")
add_subdirectory(core/utils)
set (EXTRA_LIBS ${EXTRA_LIBS} utils_core)

include_directories ("core/vlfeat")
add_subdirectory(core/vlfeat)
set (EXTRA_LIBS ${EXTRA_LIBS} vlfeat)

include_directories ("io")
add_subdirectory(io)
set (EXTRA_LIBS ${EXTRA_LIBS} io)

include_directories ("pipeline")
add_subdirectory(pipeline)
set (EXTRA_LIBS ${EXTRA_LIBS} pipeline)

if(PREPROCESSING)
    include_directories ("preprocessing")
    add_subdirectory(preprocessing)
    set (EXTRA_LIBS ${EXTRA_LIBS} preprocessing)
endif(PREPROCESSING)

if(POSTPROCESSING)
    include_directories ("postprocessing")
    add_subdirectory(postprocessing)
    set (EXTRA_LIBS ${EXTRA_LIBS} postprocessing)
endif(POSTPROCESSING)

if(MASKS)
    include_directories ("core/masks")
    add_subdirectory(core/masks)
    set (EXTRA_LIBS ${EXTRA_LIBS} masks_core)
    include_directories ("masks")
    add_subdirectory(masks)
    set (EXTRA_LIBS ${EXTRA_LIBS} masks)
endif(MASKS)

if(DIMENSIONALITY_REDUCTION)
    include_directories ("core/dim")
    add_subdirectory(core/dim)
    set (EXTRA_LIBS ${EXTRA_LIBS} dimensionality_reduction_core)
    include_directories ("dimensionality_reduction")
    add_subdirectory(dimensionality_reduction)
    set (EXTRA_LIBS ${EXTRA_LIBS} dimensionality_reduction)
endif(DIMENSIONALITY_REDUCTION)

if(ENCODING)
    include_directories ("core/encoding")
    add_subdirectory(core/encoding)
    set (EXTRA_LIBS ${EXTRA_LIBS} encoding_core)
    include_directories ("encoding")
    add_subdirectory(encoding)
    set (EXTRA_LIBS ${EXTRA_LIBS} encoding)
endif(ENCODING)

include_directories ("feature_detection")
add_subdirectory(feature_detection)
set (EXTRA_LIBS ${EXTRA_LIBS} #feature_detect_core
                              feature_detect)
#include_directories ("core/feature_detection")
#add_subdirectory(core/feature_detection)
#set (EXTRA_LIBS ${EXTRA_LIBS} #feature_detect_core)

include_directories ("feature_extraction")
add_subdirectory(feature_extraction)
set (EXTRA_LIBS ${EXTRA_LIBS} feature_extract)
include_directories ("core/feature_extraction")
add_subdirectory(core/feature_extraction)
set (EXTRA_LIBS ${EXTRA_LIBS} feature_extract_core)

include_directories ("ml")
add_subdirectory(ml)
set (EXTRA_LIBS ${EXTRA_LIBS} ml)

include_directories ("exception")
add_subdirectory(exception)
set (EXTRA_LIBS ${EXTRA_LIBS} exception)

include_directories ("logging")
add_subdirectory(logging)
set (EXTRA_LIBS ${EXTRA_LIBS} logging)

set_property(GLOBAL APPEND PROPERTY PIPELINE_LIBS ${EXTRA_LIBS})

cmake_minimum_required(VERSION 3.3)
project(pipeline_framework)

#OpenCV
find_package(OpenCV 3.0.0 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

#Boost
find_package(Boost 1.58 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

#C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/main.cpp)

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

include_directories ("${PROJECT_SOURCE_DIR}/core/exceptions")
add_subdirectory(src/core/exceptions)

include_directories ("${PROJECT_SOURCE_DIR}/core/clustering")
add_subdirectory(src/core/clustering)

include_directories ("${PROJECT_SOURCE_DIR}/core/utils")
add_subdirectory(src/core/utils)

include_directories ("${PROJECT_SOURCE_DIR}/core/vlfeat")
add_subdirectory(src/core/vlfeat)

include_directories ("${PROJECT_SOURCE_DIR}/io")
add_subdirectory(src/io)

include_directories ("${PROJECT_SOURCE_DIR}/pipeline")
add_subdirectory(src/pipeline)

if(PREPROCESSING)
    include_directories ("${PROJECT_SOURCE_DIR}/preprocessing")
    add_subdirectory(src/preprocessing)
    set (EXTRA_LIBS ${EXTRA_LIBS} preprocessing)
endif(PREPROCESSING)

if(MASKS)
    include_directories ("${PROJECT_SOURCE_DIR}/core/masks")
    add_subdirectory(src/core/masks)
    set (EXTRA_LIBS ${EXTRA_LIBS} masks_core)
    include_directories ("${PROJECT_SOURCE_DIR}/masks")
    add_subdirectory(src/masks)
    set (EXTRA_LIBS ${EXTRA_LIBS} masks)
endif(MASKS)

if(DIMENSIONALITY_REDUCTION)
    include_directories ("${PROJECT_SOURCE_DIR}/core/dim")
    add_subdirectory(src/core/dim)
    set (EXTRA_LIBS ${EXTRA_LIBS} dimensionality_reduction_core)
    include_directories ("${PROJECT_SOURCE_DIR}/dimensionality_reduction")
    add_subdirectory(src/dimensionality_reduction)
    set (EXTRA_LIBS ${EXTRA_LIBS} dimensionality_reduction)
endif(DIMENSIONALITY_REDUCTION)

if(ENCODING)
    include_directories ("${PROJECT_SOURCE_DIR}/core/encoding")
    add_subdirectory(src/core/encoding)
    set (EXTRA_LIBS ${EXTRA_LIBS} encoding_core)
    include_directories ("${PROJECT_SOURCE_DIR}/encoding")
    add_subdirectory(src/encoding)
    set (EXTRA_LIBS ${EXTRA_LIBS} encoding)
endif(ENCODING)

include_directories ("${PROJECT_SOURCE_DIR}/feature_extraction")
add_subdirectory(src/feature_extraction)

include_directories ("${PROJECT_SOURCE_DIR}/ml")
add_subdirectory(src/ml)
include_directories ("${PROJECT_SOURCE_DIR}/processing")
add_subdirectory(src/processing)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}
#                                      ${Boost_LIBRARIES}
#                                      exception
                                      clustering_core
                                      utils_core
                                      io
                                      pipeline
                                      feature_extraction
                                      ml
                                      vlfeat
                                      processing
                                      ${EXTRA_LIBS})

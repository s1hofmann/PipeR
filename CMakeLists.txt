cmake_minimum_required(VERSION 3.3)
project(pipeline_framework)

#OpenCV
find_package(OpenCV 3.0.0 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

#Boost
#find_package(Boost 1.58 COMPONENTS program_options REQUIRED)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

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

include_directories ("${PROJECT_SOURCE_DIR}/pl/core/clustering")
add_subdirectory(src/pl/core/clustering)

include_directories ("${PROJECT_SOURCE_DIR}/pl/core/utils")
add_subdirectory(src/pl/core/utils)

include_directories ("${PROJECT_SOURCE_DIR}/pl/core/vlfeat")
add_subdirectory(src/pl/core/vlfeat)

include_directories ("${PROJECT_SOURCE_DIR}/pl/io")
add_subdirectory(src/pl/io)

include_directories ("${PROJECT_SOURCE_DIR}/pl/pipeline")
add_subdirectory(src/pl/pipeline)

if(PREPROCESSING)
    include_directories ("${PROJECT_SOURCE_DIR}/pl/preprocessing")
    add_subdirectory(src/pl/preprocessing)
    set (EXTRA_LIBS ${EXTRA_LIBS} preprocessing)
endif(PREPROCESSING)

if(MASKS)
    include_directories ("${PROJECT_SOURCE_DIR}/pl/core/masks")
    add_subdirectory(src/pl/core/masks)
    set (EXTRA_LIBS ${EXTRA_LIBS} masks_core)
    include_directories ("${PROJECT_SOURCE_DIR}/pl/masks")
    add_subdirectory(src/pl/masks)
    set (EXTRA_LIBS ${EXTRA_LIBS} masks)
endif(MASKS)

if(DIMENSIONALITY_REDUCTION)
    include_directories ("${PROJECT_SOURCE_DIR}/pl/core/dim")
    add_subdirectory(src/pl/core/dim)
    set (EXTRA_LIBS ${EXTRA_LIBS} dimensionality_reduction_core)
    include_directories ("${PROJECT_SOURCE_DIR}/pl/dimensionality_reduction")
    add_subdirectory(src/pl/dimensionality_reduction)
    set (EXTRA_LIBS ${EXTRA_LIBS} dimensionality_reduction)
endif(DIMENSIONALITY_REDUCTION)

if(ENCODING)
    include_directories ("${PROJECT_SOURCE_DIR}/pl/core/encoding")
    add_subdirectory(src/pl/core/encoding)
    set (EXTRA_LIBS ${EXTRA_LIBS} encoding_core)
    include_directories ("${PROJECT_SOURCE_DIR}/pl/encoding")
    add_subdirectory(src/pl/encoding)
    set (EXTRA_LIBS ${EXTRA_LIBS} encoding)
endif(ENCODING)

include_directories ("${PROJECT_SOURCE_DIR}/pl/feature_extraction")
add_subdirectory(src/pl/feature_extraction)

include_directories ("${PROJECT_SOURCE_DIR}/pl/ml")
add_subdirectory(src/pl/ml)

include_directories ("${PROJECT_SOURCE_DIR}/pl/exception")
add_subdirectory(src/pl/exception)

include_directories ("${PROJECT_SOURCE_DIR}/pl/logging")
add_subdirectory(src/pl/logging)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}
#                                      ${Boost_LIBRARIES}
                                      clustering_core
                                      utils_core
                                      io
                                      pipeline
                                      exception
                                      logging
                                      feature_extraction
                                      ml
                                      vlfeat
                                      ${EXTRA_LIBS})

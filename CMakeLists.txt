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

include_directories ("${PROJECT_SOURCE_DIR}/core/clustering")
add_subdirectory(src/core/clustering)

include_directories ("${PROJECT_SOURCE_DIR}/core/dim")
add_subdirectory(src/core/dim)

include_directories ("${PROJECT_SOURCE_DIR}/core/encoding")
add_subdirectory(src/core/encoding)

include_directories ("${PROJECT_SOURCE_DIR}/core/filters")
add_subdirectory(src/core/filters)

include_directories ("${PROJECT_SOURCE_DIR}/core/utils")
add_subdirectory(src/core/utils)

include_directories ("${PROJECT_SOURCE_DIR}/core/vlfeat")
add_subdirectory(src/core/vlfeat)

include_directories ("${PROJECT_SOURCE_DIR}/io")
add_subdirectory(src/io)

include_directories ("${PROJECT_SOURCE_DIR}/pipeline")
add_subdirectory(src/pipeline)

include_directories ("${PROJECT_SOURCE_DIR}/dimensionality_reduction")
add_subdirectory(src/dimensionality_reduction)

include_directories ("${PROJECT_SOURCE_DIR}/encoding")
add_subdirectory(src/encoding)

include_directories ("${PROJECT_SOURCE_DIR}/feature_extraction")
add_subdirectory(src/feature_extraction)

include_directories ("${PROJECT_SOURCE_DIR}/masks")
add_subdirectory(src/masks)

include_directories ("${PROJECT_SOURCE_DIR}/ml")
add_subdirectory(src/ml)

include_directories ("${PROJECT_SOURCE_DIR}/preprocessing")
add_subdirectory(src/preprocessing)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}
                                      ${Boost_LIBRARIES}
                                      clustering_core
                                      dimensionality_reduction_core
                                      encoding_core
                                      filters_core
                                      utils_core
                                      io
                                      pipeline
                                      dimensionality_reduction
                                      encoding
                                      feature_extraction
                                      masks
                                      ml
                                      preprocessing
                                      vlfeat)

cmake_minimum_required(VERSION 3.3)
project(pipeline_framework)

#OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#Boost
find_package(Boost 1.58 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

#C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/main.cpp
        src/core/vesselfilter
        src/core/scalespace
        src/pipeline/PipeLine
        src/pipeline/PipelineStep
        src/pipeline/ConfigContainer
        src/preprocessing/PreprocessingStep
        src/preprocessing/VesselMask
        src/preprocessing/VesselMaskConfig
        src/feature_extraction/FeatureExtractionStep
        src/feature_extraction/SiftDetector
        src/feature_extraction/SiftConfigContainer src/pipeline/return_codes.h)
#                 src/encoding/EncodingStep
#                 src/encoding/VladEncoder)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})
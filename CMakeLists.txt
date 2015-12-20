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

set(SOURCE_FILES src/main.cpp
        src/core/vesselfilter
        src/core/scalespace
        src/pipeline/PipeLine
        src/pipeline/PipelineStep
        src/pipeline/ConfigContainer
        src/preprocessing/PreprocessingStep
        src/preprocessing/BinarizationStep
        src/feature_extraction/FeatureExtractionStep
        src/feature_extraction/SiftDetector
        src/feature_extraction/SiftConfigContainer
        src/pipeline/return_codes
        src/masks/MaskGenerator
        src/masks/VesselMask)
#                 src/encoding/EncodingStep
#                 src/encoding/VladEncoder)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})

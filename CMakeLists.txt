cmake_minimum_required(VERSION 3.3)
project(pipeline_framework)

#OpenCV
find_package(OpenCV REQUIRED)

#Boost
find_package(Boost 1.58 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

#C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/main.cpp
                 src/pipeline/PipeLine.cpp
                 src/pipeline/PipeLine.h
                 src/pipeline/PipelineStep.cpp
                 src/pipeline/PipelineStep.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})
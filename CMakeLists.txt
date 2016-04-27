cmake_minimum_required(VERSION 3.3)
project(pipeline_framework)

#OpenCV
find_package(OpenCV 3.0.0 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

#C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/main.cpp)

include_directories ("${PROJECT_SOURCE_DIR}/pl")
add_subdirectory(src/pl)

include_directories ("${PROJECT_SOURCE_DIR}/app")
add_subdirectory(src/app)

# Used to import the EXTRA_LIBS variable from pipeline subfolder
get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)
get_directory_property(APP_LIBS DIRECTORY src/app DEFINITION EXTRA_LIBS)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}
                                      ${PIPELINE}
                                      ${APP_LIBS})

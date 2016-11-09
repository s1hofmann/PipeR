cmake_minimum_required(VERSION 3.3)
project(piper)

#OpenCV
find_package(OpenCV 3 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

#C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

option (USE_TBB
        "Enable TBB support?" ON)

if(USE_TBB)
    add_definitions(-DUSE_TBB)
    set(CMAKE_CXX_FLAGS -ltbb)
endif(USE_TBB)

include_directories ("${PROJECT_SOURCE_DIR}/pl")
add_subdirectory(src/pl)

include_directories ("${PROJECT_SOURCE_DIR}/app")
add_subdirectory(src/app)

option (ENABLE_UI
    "Enable pipeline GUI?" OFF)

if(ENABLE_UI)
    add_definitions(-DENABLE_UI)

    include_directories ("${PROJECT_SOURCE_DIR}/ui")
    add_subdirectory(src/ui)

    get_directory_property(UI_LIBS DIRECTORY src/ui DEFINITION UI_LIBS)

    # Find the QtCore library
    find_package(Qt5Core REQUIRED)

    qt5_use_modules(${PROJECT_NAME} Core)

    target_link_libraries(${PROJECT_NAME} ${UI_LIBS})
endif(ENABLE_UI)

# Used to import the EXTRA_LIBS variable from pipeline subfolder
get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)
get_directory_property(APP_LIBS DIRECTORY src/app DEFINITION EXTRA_LIBS)
get_directory_property(APPS DIRECTORY src/app DEFINITION APPS)

foreach (app ${APPS})
    add_definitions(-D${app})
endforeach()

target_link_libraries(${PROJECT_NAME} ${PIPELINE}
                                      ${APP_LIBS})

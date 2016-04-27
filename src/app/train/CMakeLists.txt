# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtCore library
find_package(Qt5Core)

add_library (train trainingprocessor)

get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)

target_link_libraries (train Qt5::Core
                             ${PIPELINE})

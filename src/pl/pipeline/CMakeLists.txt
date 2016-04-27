# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtCore library
find_package(Qt5Core)

add_library(pipeline ConfigContainer
                     argumentprocessor
                     PipelineConfig
                     PipeLine
                     PipelineStep
                     globals)

target_link_libraries(pipeline Qt5::Core)

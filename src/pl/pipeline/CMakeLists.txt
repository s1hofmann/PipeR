# Find the QtCore library
find_package(Qt5Core)

add_library(pipeline ConfigContainer
                     argumentprocessor
                     CommandLineArgument
                     PipelineConfig
                     PipeLine
                     PipelineStep
                     globals)

target_link_libraries(pipeline ${OpenCV_LIBS}
                               Qt5::Core
                               ml)

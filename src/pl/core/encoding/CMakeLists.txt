#OpenCV
find_package(OpenCV 3 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_library(encoding_core encodingmethod
                          vladencoder
                          bowencoder)

target_link_libraries(encoding_core ${OpenCV_LIBS}
                                    exception)

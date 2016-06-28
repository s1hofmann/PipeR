add_library(utils_core progressbar
                       scalespace
                       terminfo
                       Shuffler
                       Range
                       jsoncpp)

target_link_libraries(utils_core ${OpenCV_LIBS})

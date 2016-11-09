# Find the QtCore library
find_package(Qt5Core)

add_library(io FileReader
               FileUtil
               FileWriter
               IOImpl
               bin
               csv
               img
               yml)

target_link_libraries(io ${OpenCV_LIBS}
                         Qt5::Core)

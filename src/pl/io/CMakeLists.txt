# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtCore library
find_package(Qt5Core)

#OpenCV
find_package(OpenCV 3 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

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

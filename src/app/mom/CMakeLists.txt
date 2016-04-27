# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtCore library
find_package(Qt5Xml)
find_package(Qt5Core)

add_library (mom momprocessor
                 annotationfile
                 annotationparser
                 momparser
                 evaluationobject
                 filesummary
                 foldersummary)

get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)

target_link_libraries (mom Qt5::Core
                           Qt5::Xml
                           ${PIPELINE})

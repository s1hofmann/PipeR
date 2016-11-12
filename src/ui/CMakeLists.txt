# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

add_library (ui pipelineconfigwindow)

get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)

qt5_use_modules(ui Widgets)

target_link_libraries (ui ${PIPELINE})

set (UI_LIBS ${UI_LIBS} ui)

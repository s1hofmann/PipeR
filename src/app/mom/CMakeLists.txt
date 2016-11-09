# Find the QtCore library
find_package(Qt5Xml)
find_package(Qt5Core)

option (MOM_TEXT
        "MOM text detection?" ON)
option (MOM_DECO
        "MOM decoration classification?" ON)

if(MOM_TEXT)
    add_definitions(-DMOM_TEXT)
endif(MOM_TEXT)
if(MOM_DECO)
    add_definitions(-DMOM_DECO)
endif(MOM_DECO)

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

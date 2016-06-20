# Application options
option (TRAIN
        "TRAIN application set?" ON)

option (MOM
        "MOM application set?" ON)

if(TRAIN)
    add_definitions(-DAPP_TRAIN)
    include_directories ("./train")
    add_subdirectory(./train)
    set (EXTRA_LIBS ${EXTRA_LIBS} train)
    set (APPS ${APPS} APP_TRAIN)
endif(TRAIN)

if(MOM)
    add_definitions(-DAPP_MOM)
    include_directories ("./mom")
    add_subdirectory(./mom)
    set (EXTRA_LIBS ${EXTRA_LIBS} mom)
    set (APPS ${APPS} APP_MOM)
endif(MOM)

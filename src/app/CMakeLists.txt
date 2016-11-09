# Application options
option (TRAIN
        "Enable TRAIN application?" ON)

option (OPT
        "Enable OPTIMIZE application?" ON)

option (PREDICT
        "Enable PREDICT application?" ON)

option (MOM
        "Enable MOM application?" ON)

if(TRAIN)
    add_definitions(-DAPP_TRAIN)
    include_directories ("./train")
    add_subdirectory(./train)
    set (EXTRA_LIBS ${EXTRA_LIBS} train)
    set (APPS ${APPS} APP_TRAIN)
endif(TRAIN)

if(OPT)
    add_definitions(-DAPP_OPTIMIZE)
    include_directories ("./optimize")
    add_subdirectory(./optimize)
    set (EXTRA_LIBS ${EXTRA_LIBS} opt)
    set (APPS ${APPS} APP_OPT)
endif(OPT)

if(PREDICT)
    add_definitions(-DAPP_PREDICT)
    include_directories ("./predict")
    add_subdirectory(./predict)
    set (EXTRA_LIBS ${EXTRA_LIBS} predict)
    set (APPS ${APPS} APP_PREDICT)
endif(PREDICT)

if(MOM)
    add_definitions(-DAPP_MOM)
    include_directories ("./mom")
    add_subdirectory(./mom)
    set (EXTRA_LIBS ${EXTRA_LIBS} mom)
    set (APPS ${APPS} APP_MOM)
endif(MOM)

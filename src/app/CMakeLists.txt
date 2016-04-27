# Application options
option (TRAIN
        "TRAIN application set?" ON)

option (MOM
        "MOM application set?" ON)

if(TRAIN)
    include_directories ("./train")
    add_subdirectory(./train)
    set (EXTRA_LIBS ${EXTRA_LIBS} train)
endif(TRAIN)

if(MOM)
    include_directories ("./mom")
    add_subdirectory(./mom)
    set (EXTRA_LIBS ${EXTRA_LIBS} mom)
endif(MOM)

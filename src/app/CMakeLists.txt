# Application options
option (MOM
        "MOM application set?" ON)

if(MOM)
    include_directories ("./mom")
    add_subdirectory(./mom)
    set (EXTRA_LIBS ${EXTRA_LIBS} mom)
endif(MOM)

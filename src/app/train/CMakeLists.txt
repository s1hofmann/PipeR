add_library (train trainingprocessor)

get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)

target_link_libraries (train ${PIPELINE})

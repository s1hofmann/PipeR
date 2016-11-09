add_library (opt optimizationprocessor)

get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)

target_link_libraries (opt ${PIPELINE})

add_library (predict predictor)

get_property(PIPELINE GLOBAL PROPERTY PIPELINE_LIBS)

target_link_libraries (predict ${PIPELINE})

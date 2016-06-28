add_library(preprocessing BinarizationConfig
                          BinarizationStep
                          PreprocessingStep)

target_link_libraries(preprocessing ${OpenCV_LIBS})

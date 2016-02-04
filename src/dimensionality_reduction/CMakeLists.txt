add_library(dimensionality_reduction DimensionalityReductionStep
                                     PCAConfig
                                     PCAStep)

target_link_libraries(dimensionality_reduction dimensionality_reduction_core
                                               clustering_core
                                               encoding_core
                                               io)

add_library(encoding EncodingStep
                     VladConfig
                     VladEncoder
                     descriptorpyramid
                     bowencoder
                     bowconfig)

target_link_libraries(encoding encoding_core
                               clustering_core)

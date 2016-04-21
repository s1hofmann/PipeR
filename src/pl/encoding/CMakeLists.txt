add_library(encoding EncodingStep
                     VladConfig
                     VladEncoder
                     descriptorpyramid)

target_link_libraries(encoding encoding_core)

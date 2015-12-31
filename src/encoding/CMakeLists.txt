add_library(encoding EncodingStep
                     VladConfig
                     VladEncoder)

target_link_libraries(encoding encoding_core)

add_library(encoding_core encodingmethod
                          vladencoder
                          bowencoder)

target_link_libraries(encoding_core exception)

add_library(postprocessing DBScanFilter
                           DBScanConfig
                           postprocessingstep)

target_link_libraries(postprocessing ${OpenCV_LIBS})

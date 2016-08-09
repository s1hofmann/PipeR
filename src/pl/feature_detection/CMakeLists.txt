add_library(feature_detect SiftDetectorConfig
                           siftdetector
                           featuredetectionstep)

target_link_libraries(feature_detect ${OpenCV_LIBS})

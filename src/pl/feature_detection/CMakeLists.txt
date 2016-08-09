add_library(feature_detect SiftDetectorConfig
                           SiftDetector
                           FeatureDetectionStep)

target_link_libraries(feature_detect ${OpenCV_LIBS})

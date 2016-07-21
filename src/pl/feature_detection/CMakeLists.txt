add_library(feature_detection SiftDetectorConfig)

target_link_libraries(feature_detection ${OpenCV_LIBS})

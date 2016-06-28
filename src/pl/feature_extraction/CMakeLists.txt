add_library(feature_extraction FeatureExtractionStep
                               SiftConfigContainer
                               SiftDetector)

target_link_libraries(feature_extraction ${OpenCV_LIBS})

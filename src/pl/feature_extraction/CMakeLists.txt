add_library(feature_extraction FeatureExtractionStep
                               SiftExtractorConfig
                               SiftExtractor)

target_link_libraries(feature_extraction ${OpenCV_LIBS})

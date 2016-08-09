add_library(feature_extract FeatureExtractionStep
                            FeatureConfig
                            SiftExtractorConfig
                            SiftExtractor)

target_link_libraries(feature_extract ${OpenCV_LIBS})

#OpenCV
find_package(OpenCV 3 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_library(feature_extraction FeatureExtractionStep
                               SiftConfigContainer
                               SiftDetector)

target_link_libraries(feature_extraction ${OpenCV_LIBS})

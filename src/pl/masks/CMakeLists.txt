add_library(masks MaskGenerator
                  VesselMask)

target_link_libraries(masks masks_core)

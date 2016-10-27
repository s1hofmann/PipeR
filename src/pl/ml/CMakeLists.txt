add_library(ml MLStep
               SGDStep
               MLConfig
               SGDConfig
               crossvalidation)

target_link_libraries(ml exception
                         vlfeat
                         utils_core)

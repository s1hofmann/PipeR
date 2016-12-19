add_library(ml MLStep
               SGDStep
               NCStep
               MLConfig
               SGDConfig
               NCConfig
               crossvalidation
               platt
               metrics)

target_link_libraries(ml exception
                         vlfeat
                         utils_core)

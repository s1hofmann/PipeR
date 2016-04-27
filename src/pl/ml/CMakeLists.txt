add_library(ml MLStep
               SGDStep
               SGDConfig)

target_link_libraries(ml exception
                         vlfeat)

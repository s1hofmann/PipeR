add_library(clustering_core dbscan
                            kmeanscluster)

target_link_libraries(clustering_core ${OpenCV_LIBS})

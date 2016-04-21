find_package(Threads REQUIRED)

add_library(vlfeat vl/aib
                   vl/array
                   vl/covdet
                   vl/dsift
                   vl/fisher
                   vl/generic
                   vl/getopt_long
                   vl/gmm
                   vl/heap-def
                   vl/heap
                   vl/heap-t
                   vl/hikmeans
                   vl/hog
                   vl/homkermap
                   vl/host
                   vl/ikmeans
                   vl/imop
                   vl/imopv
                   vl/imopv_sse2
                   vl/kdtree
                   vl/kmeans
                   vl/lbp
                   vl/liop
                   vl/mathop_avx
                   vl/mathop
                   vl/mathop_sse2
                   vl/mser
                   vl/pgm
                   vl/qsort-def
                   vl/quickshift
                   vl/random
                   vl/rodrigues
                   vl/scalespace
                   vl/shuffle-def
                   vl/sift
                   vl/slic
                   vl/stringop
                   vl/svmdataset
                   vl/svm
                   vl/vlad
                   wrapper/sdcasolver
                   wrapper/sgdsolver
                   wrapper/svm_solver)

target_link_libraries(vlfeat ${CMAKE_THREAD_LIBS_INIT})

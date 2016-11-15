add_library(findfk_libs
  WeightedQuickUnionPathCompression.cc
  aggregation.cc)

target_link_libraries(findfk_libs)

add_executable(findfk findfk.cc)
target_link_libraries(findfk findfk_libs)

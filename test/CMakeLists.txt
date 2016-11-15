file(GLOB test_headers [a-zA-Z]*.hpp)
file(GLOB test_sources [a-zA-Z]*.cc)

include_directories(
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/test)

add_executable(unit_test
  ${test_sources})

target_link_libraries(unit_test
  findfk_libs)

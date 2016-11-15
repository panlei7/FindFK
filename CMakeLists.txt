cmake_minimum_required(VERSION 2.8)

project(FindFK CXX)
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -g -O2")

find_package(yaml-cpp 0.5 REQUIRED)
if(yaml-cpp_FOUND)
  message("yaml-cpp found")
  include_directories(${YAML_CPP_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Cannot find yaml-cpp")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME test COMMAND unit_test)

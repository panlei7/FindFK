cmake_minimum_required(VERSION 2.8)

project(FindFK CXX)
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -g -O2")

# find_package(Armadillo 7.0 REQUIRED)

# if(ARMADILLO_FOUND)
#   message("armadillo found")
#   include_directories(${ARMADILLO_INCLUDE_DIRS})
# else()
#   message(FATAL_ERROR "Cannot find Armadillo")
# endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME test COMMAND unit_test)

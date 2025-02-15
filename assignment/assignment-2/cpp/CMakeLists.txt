cmake_minimum_required(VERSION 3.30)
project(csci4430-assignment2-s25)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Ensure that output executables are in the build/bin directory
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Use local dependencies instead of fetching
add_subdirectory(${CMAKE_SOURCE_DIR}/../deps/pugixml ${CMAKE_BINARY_DIR}/pugixml)
add_subdirectory(${CMAKE_SOURCE_DIR}/../deps/spdlog ${CMAKE_BINARY_DIR}/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/../deps/cxxopts ${CMAKE_BINARY_DIR}/cxxopts)

find_package(Boost REQUIRED COMPONENTS regex)

# Recurse through the subdirectories
add_subdirectory(src)

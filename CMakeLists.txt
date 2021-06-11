cmake_minimum_required(VERSION 3.5.1)
project(beegenerator VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(libs)

add_subdirectory(src)
configure_file(src/beegeneratorConfig.h.in beegeneratorConfig.h)

add_subdirectory(test)

target_include_directories(beegenerator PUBLIC "${PROJECT_BINARY_DIR}")



# CMake minimum version
cmake_minimum_required(VERSION 3.12)

# Project name
project(Blockchain)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# Add source files
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)
add_executable(blockchain ${SOURCE_FILES})

target_include_directories(blockchain PRIVATE ${INCLUDE_DIR})

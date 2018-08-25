# CMake 3.8 is the earliest version that knows about C++17 flags
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE CACHE BOOL "")
set(CMAKE_CXX_EXTENSIONS FALSE CACHE BOOL "")

# Always generate a compile_commands.json file if supported by the
# current generator. Makes it easier to run tools such as clang-tidy and
# oclint.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")

project(gslam)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(thirdparty)

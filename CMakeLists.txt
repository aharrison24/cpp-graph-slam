# CMake 3.8 is the earliest version that knows about C++17 flags
cmake_minimum_required(VERSION 3.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE CACHE BOOL "")
set(CMAKE_CXX_EXTENSIONS FALSE CACHE BOOL "")

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")

set(CMAKE_MACOSX_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

if (APPLE)
  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
elseif(UNIX)
  set(CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")
endif()

# Default build type (user can override it in the cache)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")

# Constrain build type drop-down to contain only valid build types
set_property(CACHE CMAKE_BUILD_TYPE
  PROPERTY STRINGS
  Release Debug RelWithDebInfo MinSizeRel
)

# Always generate a compile_commands.json file if supported by the
# current generator. Makes it easier to run tools such as clang-tidy and
# oclint.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")

project(gslam
  VERSION 0.0.1
  LANGUAGES CXX
)

include(CTest)

add_subdirectory(thirdparty)
add_subdirectory(dummy)

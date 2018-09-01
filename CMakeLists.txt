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

option(CONAN_AUTO_UPDATE "Automatically run 'conan install <src>' if necessary" OFF)
if(EXISTS "${CMAKE_BINARY_DIR}/conan_paths.cmake")
  if ("${CMAKE_SOURCE_DIR}/conanfile.txt" IS_NEWER_THAN
      "${CMAKE_BINARY_DIR}/conan_paths.cmake")
    if(CONAN_AUTO_UPDATE)
      message("conan_paths.txt file out-of-date. Regenerating it...")
      execute_process(
        COMMAND conan install "${CMAKE_SOURCE_DIR}" --build missing
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
      )
    else()
        message(FATAL_ERROR "It looks like your conan_paths.cmake file "
          "is out-of-date. Please run the following commands:\n"
          "cd \"${CMAKE_BINARY_DIR}\"\nconan install \"${CMAKE_SOURCE_DIR}\" "
          "--build missing\n"
          "If you want this to happen automatically in future, set the "
          "CONAN_AUTO_UPDATE cache option to ON"
        )
    endif()
  endif()

  message("Found \"conan_paths.cmake\" file. "
    "Using Conan to provide dependencies.")
  include("${CMAKE_BINARY_DIR}/conan_paths.cmake")
endif()

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
if(NOT TARGET SFML::SFML)
  add_library(SFML::SFML INTERFACE IMPORTED)

  set_target_properties(SFML::SFML PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SFML_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${SFML_LIBRARIES}"
  )
endif()


add_subdirectory(thirdparty)
add_subdirectory(dummy)
add_subdirectory(src)

# ---------------------------
# Binary directory config

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT gslam-targets
  FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-targets.cmake"
  NAMESPACE gslam::
)

configure_file(${PROJECT_NAME}-config.cmake.in
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  @ONLY
)

# ---------------------------
# Install prefix config
set(INSTALL_CONFIG_DIR share/cmake/gslam)
install(
  EXPORT gslam-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE gslam::
  DESTINATION "${INSTALL_CONFIG_DIR}"
)

install(
  FILES
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  DESTINATION
    "${INSTALL_CONFIG_DIR}"
)

# ---------------------------
include(UninstallTarget)

# ---------------------------
set(CPACK_PACKAGE_VENDOR "ARH")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Graph SLAM experiments")
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

cmake_minimum_required(VERSION 3.27)
project(HELLO CXX)

set(CMAKE_CXX_STANDARD 23 CACHE STRING "C++ standard to use for the whole project")

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(modules)

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

add_module_library(hello hello.cc)

add_executable(main main.cc)
target_link_libraries(main PRIVATE
  hello
  sfml::sfml
)
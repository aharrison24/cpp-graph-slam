add_library(catch2 INTERFACE)
target_include_directories(catch2
  SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Cause all Catch2 macros to be prefixed with 'CATCH_' to avoid name
# clashes.
target_compile_definitions(catch2
  INTERFACE
  "CATCH_CONFIG_PREFIX_ALL"
)

add_library(catch2_main STATIC catch2_main.cpp)
target_link_libraries(catch2_main PUBLIC catch2)

# Disable clang-tidy for catch2_main library
set_target_properties(
    catch2_main
    PROPERTIES
         CXX_CLANG_TIDY ""
)

add_library(Catch2::Catch2 ALIAS catch2)
add_library(Catch2::Main ALIAS catch2_main)


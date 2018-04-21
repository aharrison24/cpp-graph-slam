add_executable(dummy_test dummy_test.cpp)
target_link_libraries(dummy_test
  PRIVATE
    gslam::dummy
    Catch2::Main
)

set_target_properties(dummy_test
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests"
)

add_test(
  NAME dummy_test
  COMMAND dummy_test
  WORKING_DIRECTORY $<TARGET_FILE_DIR:dummy_test>
)

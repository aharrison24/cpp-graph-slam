add_executable(slam_viewer
  slam_viewer.cpp
)

target_link_libraries(slam_viewer
  PRIVATE
    SFML::SFML
)

# toplevel CMakeLists.txt for a catkin workspace
# catkin/cmake/toplevel.cmake

cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(robotics_rrt)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  visualization_msgs
  tf
)

include_directories(
  lib
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(robotics_rrt src/demo.cpp include/workspace.h src/workspace.cpp include/node.h src/node.cpp include/tree.h src/tree.cpp src/obstacle.cpp include/obstacle.h)
target_link_libraries(robotics_rrt ${catkin_LIBRARIES})

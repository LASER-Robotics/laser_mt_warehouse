cmake_minimum_required(VERSION 3.1.2)
project(laser_turtlebot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  actionlib
  move_base_msgs
  geometry_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES MoveTurtlebot 
  CATKIN_DEPENDS roscpp geometry_msgs
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_library(MoveTurtlebot src/move_turtlebot.cpp)

add_dependencies(MoveTurtlebot
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(MoveTurtlebot
  ${catkin_LIBRARIES}
)
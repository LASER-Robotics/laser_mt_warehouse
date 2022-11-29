################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.0.2)
project(turtlebot_simulation)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  tf
  gazebo_ros
)

find_package(gazebo REQUIRED)


################################################################################
# Setup for python modules and scripts
################################################################################

################################################################################
# Declare ROS messages, services and actions
################################################################################

################################################################################
# Declare ROS dynamic reconfigure parameters
################################################################################

################################################################################
# Declare catkin specific configuration to be passed to dependent projects
################################################################################
catkin_package(
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs geometry_msgs nav_msgs tf gazebo_ros
  DEPENDS GAZEBO
)


################################################################################
# Build
################################################################################
link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)

################################################################################
# Install
################################################################################
install(DIRECTORY launch maps param rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)           

################################################################################
# Test
################################################################################

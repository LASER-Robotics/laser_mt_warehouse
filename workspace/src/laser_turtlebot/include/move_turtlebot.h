#pragma once
#ifndef MOVE_TURTLEBOT_H
#define MOVE_TURTLEBOT_H

/* includes //{ */

/* each ROS nodelet must have these */
#include <ros/ros.h>
#include <ros/package.h>
#include <nodelet/nodelet.h>

#include <geometry_msgs/Pose.h>
//}

namespace laser_turtlebot{

/* class MoveTurtlebot //{ */
class MoveTurtlebot : public nodelet::Nodelet {
  
public:
  virtual void onInit();
  int getWayPointsSize();
  int getGoalsSize();
  void setGoals();
  void startPath();

private:
  /* flags must be initialized with the default value */
  bool is_initialized_ = false;
  
  /* ROS parameters are distinguished by underscore at the beginning and the end */
  std::string _example_parameter_;

  std::vector<double> _waypoints_;

  std::vector<geometry_msgs::Pose> goals_;
};  

//}

} // namespace laser_turtlebot

#endif
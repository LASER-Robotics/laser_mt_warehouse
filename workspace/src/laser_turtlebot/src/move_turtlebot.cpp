#include <move_turtlebot.h>
#include <pluginlib/class_list_macros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

namespace laser_turtlebot {
  
  typedef actionlib::SimpleActionClient <move_base_msgs::MoveBaseAction> MoveBaseClient;

  int MoveTurtlebot::getWayPointsSize(){
    return _waypoints_.size();
  }

  void MoveTurtlebot::setGoals(){
    for(int i = 0; i < _waypoints_.size(); i = i + 2){
      geometry_msgs::Pose pose;

      pose.position.x = _waypoints_[i];
      pose.position.y = _waypoints_[i + 1];
      pose.position.z = 0.0;

      pose.orientation.x = 0;
      pose.orientation.y = 0;
      pose.orientation.z = 0; 
      pose.orientation.w = 1.0;

      goals_.push_back(pose);
    }
  }

  void MoveTurtlebot::startPath(){
    MoveBaseClient ac("move_base", true);
    
    while(!ac.waitForServer (ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	  }
    move_base_msgs::MoveBaseGoal goal;
    // set up the frame parameters
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    for (int i = 0; i < goals_.size(); i++){
      // Define a position and orientation for the robot to reach
      goal.target_pose.pose = goals_[i];

      // Send the goal position and orientation for the robot to reach
      ROS_INFO ("Sending goal - x: %s / y: %s ", std::to_string(goals_[i].position.x).c_str(), std::to_string(goals_[i].position.y).c_str());
      ac.sendGoal (goal);
      // Wait an infinite time for the results
      ac.waitForResult();
      
      ros::Duration(5.0).sleep();
    }
	  // Check if the robot reached ts goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO( "Hooray, reached drop off zone");
    else
      ROS_INFO("The base failed to move forward");
  }
    
  /* onInit() //{ */
  void MoveTurtlebot::onInit() {

    /* obtain node handle */
    ros::NodeHandle nh = nodelet::Nodelet::getMTPrivateNodeHandle();

    /* waits for the ROS to publish clock */
    ros::Time::waitForValid();

    bool load_sucessfully = true;

    //load_sucessfully = load_sucessfully && nh.getParam("example_parameter", _example_parameter_);

    load_sucessfully = load_sucessfully && nh.getParam("waypoints", _waypoints_);  

    if (!load_sucessfully) {
      ROS_ERROR("Could not load non-optional parameters!");
      ros::shutdown();
    }

    ROS_INFO_ONCE("[MoveTurtlebot]: initialized!");
    ROS_INFO_ONCE("[MoveTurtlebot]: %d params", MoveTurtlebot::getWayPointsSize());
    MoveTurtlebot::setGoals();
    ROS_INFO_ONCE("[MoveTurtlebot]: goals setted!");
    MoveTurtlebot::startPath();
    is_initialized_ = true;
  }

  

} // namespace laser_turtlebot

PLUGINLIB_EXPORT_CLASS(laser_turtlebot::MoveTurtlebot, nodelet::Nodelet);

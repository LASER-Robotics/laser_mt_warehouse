import rospy
import yaml
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import actionlib
from actionlib_msgs.msg import *
from geometry_msgs.msg import Pose, Point, Quaternion

class Turtle:
    def __init__(self, ID):
        self.shelfNumber = 0
        
        rospy.init_node("follow_route", anonymous = False)
        
        self.move_base = actionlib.SimpleActionClient('move_base', MoveBaseAction)
        rospy.loginfo("Wait for the action server to come up")
        self.move_base.wait_for_server(rospy.Duration(5))
        
        with open("/home/turtlebot/Mambo-Turtle-Warehouse/Turtlebot2/src/route" + ID + ".yaml", "r") as stream:
            self.mapPoints = yaml.load(stream)
                
    def go_to_shelf(self):
        name = self.mapPoints[self.shelfNumber]['filename']

        # Navigation
        rospy.loginfo("Go to %s pose", name)
        
        self.goal = MoveBaseGoal()
        self.goal.target_pose.header.frame_id = 'map'
        self.goal.target_pose.header.stamp = rospy.Time.now()
        self.goal.target_pose.pose = Pose(Point(self.mapPoints[self.shelfNumber]['position']['x'], self.mapPoints[self.shelfNumber]['position']['y'], 0.000),
									Quaternion(self.mapPoints[self.shelfNumber]['quaternion']['r1'], self.mapPoints[self.shelfNumber]['quaternion']['r2'], self.mapPoints[self.shelfNumber]['quaternion']['r3'], self.mapPoints[self.shelfNumber]['quaternion']['r4']))
        self.move_base.send_goal(self.goal)
        
        success = self.move_base.wait_for_result(rospy.Duration(60)) 
        state = self.move_base.get_state()
        
        if not success and not state == GoalStatus.SUCCEEDED:
                self.move_base.cancel_goal()
                rospy.loginfo("Failed to reach %s pose", name)
                rospy.loginfo("Reached %s pose", name)
                
                self.go_to_shelf()
        
        self.shelfNumber += 1
        
        return self.shelfNumber

    def check_end_route(self):
        if self.shelfNumber == 2:
            return True
        else:
            return False 
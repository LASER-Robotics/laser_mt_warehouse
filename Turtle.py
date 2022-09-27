import rospy
import yaml
import actionlib
from actionlib_msgs.msg import *
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from geometry_msgs.msg import Pose, Point, Quaternion
#from tf.transformations import euler_from_quaternion

class Turtle:
        def __init__(self):
                with open("Turtlebot2/src/route.yaml", "r") as stream:
                        self.mapPoints = yaml.load(stream)
                
                self.move_base = actionlib.SimpleActionClient("move_base", MoveBaseAction)
                self.move_base.wait_for_server(rospy.Duration(5))
                

        def go_to_shelf(self):
                print(self.mapPoints["position"]["x"])
                print(self.mapPoints["position"]["y"])
                print(self.mapPoints["quartenion"])

                self.pos = MoveBaseGoal()

                self.pos.target_pose.header.frame_id = "map"
                self.pos.target_pose.header.stamp = rospy.Time.now()
                self.pos.target_pose.pose = Pose(Point(self.mapPoints["position"]["x"], self.mapPoints["position"]["y"], 0), 
                                        Quaternion(self.mapPoints["quartenion"]["r1"], self.mapPoints["quartenion"]["r2"], self.mapPoints["quartenion"]["r3"], self.mapPoints["quartenion"]["r4"]))

                self.move_base.send_goal(self.pos)
                
                result = False

                for x in range(2):
                        sucess = self.move_base.wait_for_result(rospy.Duration(60))
                        state = self.move_base.get_state()

                        if sucess and state == GoalStatus.SUCCEEDED:
                                result = True
                                break                
                
                return result
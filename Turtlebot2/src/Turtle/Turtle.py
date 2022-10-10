from turtle import pos
import rospy
import yaml
import actionlib
from actionlib_msgs.msg import *
from move_base_msgs.msg import MoveBaseGoal
from geometry_msgs.msg import Pose, Point, Quaternion, PoseStamped
#from tf.transformations import euler_from_quaternion

class Turtle:
        def __init__(self):
                with open("Turtlebot2/src/route.yaml", "r") as stream:
                        self.mapPoints = yaml.load(stream)
                
                self.pub = rospy.Publisher("move_base_simple/goal", PoseStamped, queue_size=1)
                #self.move_base = actionlib.SimpleActionClient("move_base", MoveBaseAction)
                #self.move_base.wait_for_server(rospy.Duration(5))
                

        def go_to_shelf(self):
                self.pos = PoseStamped()

                print("antes dos pontos")
                self.pos.header.frame_id = "map"
                self.pos.header.stamp = rospy.Time.now()
                self.pos.pose = Pose(Point(6, 15, 0), Quaternion(0, 0, 0.3, 0.9))

                #Pose(Point(self.mapPoints[0]["position"]["x"], self.mapPoints[0]["position"]["y"], 0), 
                 #                       Quaternion(self.mapPoints[0]["quaternion"]["r1"], self.mapPoints[0]["quaternion"]["r2"], self.mapPoints[0]["quaternion"]["r3"], self.mapPoints[0]["quaternion"]["r4"]))

                self.pub.publish(self.pos)
                
                print("depois dos pontos")
                #result = False

                #for x in range(2):
                      #  sucess = self.move_base.wait_for_result(rospy.Duration(5))
                       # state = self.move_base.get_state()

                        #if sucess and state == GoalStatus.SUCCEEDED:
                         #       print("consegui passar")
                          #      result = True
                           #     break                
                
                return 
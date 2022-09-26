from time import sleep
import rospy
from  move_base_msgs import MoveBaseActionGoal 
from tf.transformations import euler_from_quaternion

class Turtle:
        def __init__(self):
                self.moving = False
                self.shelf_number = 0
                self.poses[[]]
                
                self.pub_pose = rospy.Publisher("goal", MoveBaseActionGoal, queue_size=1)
                self.sub_pose = rospy.Subscriber("topic", , check_pose)
                

        def check_pose(self, odom):
                margin = 1.25

                if odom.position.x <= (margin + self.poses[self.shelf_number][0]) and odom.position.y <= (margin + self.poses[self.shelf_number][1]) and odom.position.z <= (margin + self.poses[self.shelf_number][2]):
                        self.moving = False

                return

        def go_to_shelf(self, shelf_number):
                self.shelf_number = shelf_number
                self.pos = PoseStamped()

                self.pos.position.x = self.poses[shelf_number][0]
                self.pos.position.y = self.poses[shelf_number][1]
                self.pos.position.z = self.poses[shelf_number][2]

                self.pos.orientation = euler_from_quaternion(self.poses[shelf_number, 4])

                self.pub_pose.publish(pos)

                while not self.moving:
                        sleep(20)

                return True
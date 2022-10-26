from Turtle import Turtle
import rospy

rospy.init_node("follow_route", anonymous = False)

test = Turtle()

test.go_to_shelf()
test.go_to_shelf()
test.go_to_shelf()
test.go_to_shelf()


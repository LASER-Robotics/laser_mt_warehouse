from Mambo.src.Drone import Drone
from Turtlebot2.src.Turtle import Turtle

mambo = Drone("?????????")

if not mambo.get_connectionState():
    exit()

turtle = Turtle(ID="2")

end_route = False
status_turtle = turtle.go_to_shelf()

while not end_route:
    if status_turtle == 1:
        status_mambo = mambo.fly()

        if status_mambo:
            turtle.go_to_shelf()
    
    end_route = turtle.check_end_route()
            
mambo.disconnect()
from pyparrot.Minidrone import Mambo
import comunicacion

mamboAddress = "d0:3a:62:2d:e6:3b"

mambo = Mambo(mamboAddress, False)
connectionState = mambo.connect(3)
print(f"Estate of connection {connectionState}")

signalTurtle = False

if connectionState:
    while (True):
        signalTurtle = comunicacion.checkSignalTurtle()

        if signalTurtle == "End of route":
            mambo.disconnect()
            break

        if signalTurtle == "False":
            print("Sleeping")
            mambo.sleep()
        else:
            print("Take off")
            mambo.safe_takeoff()

            print("Flying")
            mambo.fly_direct(0, 0, 0, 20, 5)
            
#endereço bluetooth do drone com 4 hélices:
#d0:3a:62:2d:e6:3b

#endereço bluetooth do drone com adesivo
#d0:3a:64:1f:e6:3b

from pyparrot.Minidrone import Mambo
import comunicacion

enderecoMambo = "d0:3a:62:2d:e6:3b"

mambo = Mambo(enderecoMambo, False)
connectionState = mambo.connect(3)
print(f"Estate of connection {connectionState}")

signalTurtle = False

def searchPacket():
    while True:
        mambo.fly_direct(0,0,0,5,1)
        if comunicacion.checkQR() == "True":
            return True
        elif comunicacion.checkQR() == "True and Last floor":
            return "True and Last floor"

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

        while signalTurtle == "True":
            print("Search packet")
            if searchPacket():
                mambo.hover()
            elif searchPacket() == "True and Last floor":
                mambo.safe_land()
                comunicacion.warnLanded()
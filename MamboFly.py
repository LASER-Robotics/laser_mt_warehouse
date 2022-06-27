#endereço bluetooth do drone com 4 hélices:
#d0:3a:62:2d:e6:3b

#endereço bluetooth do drone com adesivo
#d0:3a:64:1f:e6:3b

from pyparrot.Minidrone import Mambo
import comunicacion

enderecoMambo = "d0:3a:62:2d:e6:3b"

mambo = Mambo(address=enderecoMambo, use_wifi=False)
connectionState = mambo.connect(num_retries=3)
print(f"Estate of connection {connectionState}")

signalTurtle = False

def hover():
    mambo.hover()

def sleep():
    mambo.smart_sleep()

def takeOff():
    mambo.safe_takeoff()

def land():
    mambo.safe_land()

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
            sleep()
        else:
            print("Take off")
            takeOff()

        while signalTurtle == "True":
            print("Search packet")
            if searchPacket():
                hover()
            elif searchPacket() == "True and Last floor":
                land()
                comunicacion.warnLanded()
from pyparrot.Minidrone import Mambo

class Drone:
    def __init__(self, addres):
        self.mambo = Mambo(self.mamboAddress, False)
        self.connectionState = self.mambo.connect(3)
        print(f"Drone: Connection estate: {self.connectionState}")

    def fly(self):
        if self.connectionState:
            print("Drone: Going up")
            self.mambo.safe_takeoff(2)
            self.mambo.fly_direct(0, 0, 0, 16, 8)
            self.mambo.smart_sleep(1)
            self.mambo.fly_direct(0, 0, 0, -10, 12)
            self.mambo.safe_land(2)

    def disconnect(self):
        print("Drone: disconected")
        self.mambo.disconnect()

            
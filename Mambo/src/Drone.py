from pyparrot.Minidrone import Mambo

class Drone:
    def __init__(self, mamboAdress):
        self.mambo = Mambo(mamboAdress, False)
        self.connectionState = self.mambo.connect(3)
        print(f"Drone: Connection estate: {self.connectionState}")

    def get_connectionState(self):
        return self.connectionState
    
    def fly(self):
        if self.connectionState:
            print("Drone: Going up")
            self.mambo.safe_takeoff(100)
            self.mambo.fly_direct(0, 0, 0, 16, 7)
            self.mambo.smart_sleep(1)
            self.mambo.fly_direct(0, 0, 0, -10, 12)
            self.mambo.safe_land(100)

            return True

    def disconnect(self):
        print("Drone: disconected")
        self.mambo.disconnect()

            

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
<<<<<<< HEAD
            self.mambo.fly_direct(0, 0, 0, 16, 7)
=======
            self.mambo.fly_direct(0, 0, 0, 16, 8)
>>>>>>> bc6f1c7ce658d8b54ec142e3b95aba6048232feb
            self.mambo.smart_sleep(1)
            self.mambo.fly_direct(0, 0, 0, -10, 12)
            self.mambo.safe_land(100)

            return True

    def disconnect(self):
        print("Drone: disconected")
        self.mambo.disconnect()

            

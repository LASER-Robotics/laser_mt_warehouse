from pyparrot.Minidrone import Mambo

mambo = Mambo("d0:3a:62:2d:e6:3b", False)


sucesso = mambo.connect(3)

if sucesso:
    mambo.smart_sleep(3)
    mambo.ask_for_state_update()
    mambo.smart_sleep(3)

    if mambo.sensors.flying_state != "emergency":
        print("subindo")
        for i in range(1):
            mambo.safe_takeoff(1)
            mambo.smart_sleep(2)
            mambo.fly_direct(0, 0, 0, 14, 11)
            mambo.fly_direct(0, 0, 0, -10, 14)
            mambo.safe_land(5)

    mambo.disconnect()
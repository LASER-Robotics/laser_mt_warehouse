from pyparrot.Minidrone import Mambo

mambo = Mambo("d0:3a:62:2d:e6:3b", False)

sucesso = mambo.connect(3)

if sucesso:
    mambo.smart_sleep(3)
    mambo.ask_for_state_update()
    mambo.smart_sleep(3)

    if mambo.sensors.flying_state != "emergency":
        print("subindo")
        mambo.safe_takeoff(3)
        opa = mambo.fly_direct(0, 0, 0, 5, 5)
        print(opa)
        mambo.safe_land(3)

    mambo.disconnect()
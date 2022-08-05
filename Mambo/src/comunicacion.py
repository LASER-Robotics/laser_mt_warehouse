import paho.mqtt.client as mqtt

signal = ""
nameClient = "DroNE01"

def on_message(client, userdata, message):
    signal = str(message.payload.decode("utf-8"))

client = mqtt.Client(nameClient)
client.on_message=on_message
client.connect("broker.hivemq.com")

def checkQR():
    client.subscribe("CamerA01")
    return signal

def warnLanded():
    client.publish("TurTLeSignalLanded", "True")

def checkSiganlTurtle():
    client.subscribe("TurTLeSignalTakeOFF")
    return signal
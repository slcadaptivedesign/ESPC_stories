import paho.mqtt.client as mqtt
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " +str(rc))
    client.subscribe("David")
def on_message(client, userdata, msg):
    print(str(msg.payload))
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("192.168.2.2", 1883, 60)
client.loop_forever()
    

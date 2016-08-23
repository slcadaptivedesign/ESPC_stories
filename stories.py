import os
import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO
import time
import os

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(21, GPIO.OUT)
GPIO.setup(12, GPIO.OUT)
#personal USB power device
GPIO.setup(25, GPIO.OUT)

#unclear if global is actually set here or line 46
global buttoncount
buttoncount = 0
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " +str(rc))
    client.subscribe("David")

def on_message(client, userdata, msg):
    print(str(msg.payload))
    list_dir = []
    list_dir = os.listdir("/home/pi/Desktop/musictest")
    list_dir.sort()
    print(list_dir)
    count = 0
    for file in list_dir:
        if file.endswith(".m4a") or file.endswith(".wav"):
            count += 1
    #turns on fan
    if msg.payload == "2":
        GPIO.output(21, GPIO.HIGH)
        time.sleep(30)
        GPIO.output(21, GPIO.LOW)
    #turns on the light
    elif msg.payload == "3":
        GPIO.output(12, GPIO.HIGH))
        time.sleep(30)
        GPIO.output(12,GPIO.LOW)
    #Don't need GPIO pin for music, uses wifi to connect.
    elif msg.payload == "4":
        filestring = list_dir[buttoncount]
        print("home/pi/Desktop/musictest/" +str(filestring))
        os.system("omxplayer /home/pi/Desktop/musictest/" +str(filestring))
        #unclear if global is set here or line 46
        global buttoncount
        buttoncount += 1
    elif msg.payload == "5":
        GPIO.output(25, GPIO.HIGH)
        time.sleep(30)
        GPIO.output(25, GPIO.LOW)
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
ipad = os.system("hostname -I")
ipad = str(ipad)
client.connect(ipad, 1883, 60)
client.loop_forever()
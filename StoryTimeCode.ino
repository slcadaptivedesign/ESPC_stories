/***************************************************
  Adafruit MQTT Library ESP8266 Example
  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino
  Works great with Adafruit's Huzzah ESP board:
  ----> https://www.adafruit.com/product/2471
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Tony DiCola for Adafruit Industries.
  Adafruit IO example additions by Todd Treece.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// function prototypes
void connect(void);

/****************************** Pins ******************************************/
//music button
#define BUTTON          2 //has a pull-up resistor attached
#define Button2         5
#define Button3         14
#define Button4         15 //has a pull-down resistor attached

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "WRITE THE SSID"
#define WLAN_PASS       "WRITE THE PASSWORD"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "WRITE THE SERVER #"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "WRITE USERNAME"
#define AIO_KEY         ""

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Store the MQTT server, client ID, username, and password in flash memory.
// This is required for using the Adafruit MQTT library.
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;
// Set a unique MQTT client ID using the AIO key + the date and time the sketch
// was compiled (so this should be unique across multiple devices for a user,
// alternatively you can manually set this to a GUID or other random value).
const char MQTT_CLIENTID[] PROGMEM  = __TIME__ AIO_USERNAME;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);/****************************** Feeds ***************************************/

// Setup a feed called 'button' for publishing changes.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
const char BUTTON_FEED[] PROGMEM = AIO_USERNAME "";
Adafruit_MQTT_Publish button = Adafruit_MQTT_Publish(&mqtt, BUTTON_FEED);
Adafruit_MQTT_Publish button2 = Adafruit_MQTT_Publish(&mqtt, BUTTON_FEED);
Adafruit_MQTT_Publish button3 = Adafruit_MQTT_Publish(&mqtt, BUTTON_FEED);
Adafruit_MQTT_Publish button4 = Adafruit_MQTT_Publish(&mqtt, BUTTON_FEED);

/*************************** Sketch Code ************************************/

// button state
int current = 0;
int last = -1;
int current2 = 0;
int last2 = -1;
int value, value2, value3, value4;

void setup() {

  // set button pin as an input
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(Button3, INPUT);
  pinMode(Button3, INPUT);
  pinMode(Button4, INPUT);

  Serial.begin(115200);

  Serial.println(F("Adafruit IO Example"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  // connect to adafruit io
  connect();

}

void loop() {

  // ping adafruit io a few times to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }

  // grab the current state of the button
  current = digitalRead(BUTTON);
  current2 = digitalRead(Button2);
  current3 = digitalRead(Button3);
  current4 = digitalRead(Button4);

  if (current == LOW){
    value = 2;
    Serial.print(F("\nSending button value: "));
    Serial.println(value);
    button.publish(value);
  }
  else if (current == HIGH){
    value = 0;}

  if (current2 == LOW){
    value2 = 3;
    Serial.print(F("\nSending button value: "));
    Serial.print(value2);
    button2.publish(value2);  
    }
  else if (current2 == HIGH) {
    value2 = 0;
  }
  if (current3 == LOW){
    value3 = 4;
    Serial.print(F("/nSending button value: "));
    Serial.print(value3);
    button3.publish(value3);
  }
  else if (current3 == HIGH){
    value3 = 0;
  }
  if (current4 == HIGH){ //needs to be HIGH for true because of the pull-down resistor
    value4 = 5;
    Serial.print(F("/nSending button value: "));
    Serial.print(value4);
    button4.publish(value4);
  }
  else if (current4 == LOW){
    value4 = 0;
  }
  // return if the value hasn't changed
//  if(current == last) //&& current2 == last2);
//    return;

//  int32_t value = (current == LOW ? 2 : 0);
//  int32_t value2 = (current2 == HIGH ? 3 : 0);
  // Now we can publish stuff!
//  Serial.print(F("\nSending button value: "));
//  Serial.print(value);
//  Serial.print(value2);
  //Serial.print("... ");

//  if (! button.publish(value))
//    Serial.println(F("Failed."));
//  else if (! button.publish(value2))
//    Serial.println(F("Failed."));
//  else
//    Serial.println(F("Success!"));

  // save the button state
//  last = current;
//  last2 = current2;

}

// connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}

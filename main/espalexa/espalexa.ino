/*
 * This is a basic example on how to use Espalexa and its device declaration methods.
 */ 
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include <ESP8266WiFi.h>


// prototypes
boolean connectWifi();
#define OUT1 2 // D4

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

// Change this!!
const char* ssid = "wifi-ssid";
const char* password = "xxx";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    espalexa.addDevice("Corridor Light", corridorLightChanged, 255);
    espalexa.begin();
    // LED
    pinMode(OUT1, OUTPUT);
    digitalWrite(OUT1, HIGH);    
  } else {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop() {
  espalexa.loop();
  delay(1);
}

void corridorLightChanged(uint8_t brightness) {
  Serial.print("Corridor Light changed to ");
  if (brightness) {
    Serial.print("ON, brightness ");
    Serial.println(brightness);
    digitalWrite(OUT1, HIGH);
  }
  else  {
    Serial.println("OFF");
    digitalWrite(OUT1, LOW);
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

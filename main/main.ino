/*
  Web client

  This sketch connects to a website (http://arduino.cc)
  using the WiFi module.

  created 13 July 2010
  by dlf (Metodo2 srl)
  modified 31 May 2012
  by Tom Igoe
*/
#define D4 2

// void setup() {
//   pinMode(D4, OUTPUT);
//   Serial.begin(9600);
//   Serial.println("selaminaleykum");
// }

// void loop() {
//   delay(1000);
//   digitalWrite(D4, LOW);
//   Serial.println("bi saniye oldu");
//   // delay(100);
//   // digitalWrite(D1, HIGH);
//   // digitalWrite(D4, HIGH);
//   // delay(100);
//   // digitalWrite(D4, LOW);
// }
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "FRITZ!Box 6820 RP"
#define STAPSK  "34383272287906888123"
#endif

const char* ssid = STASSID;
const char* pass = STAPSK;

const char* server = "arduino.cc";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println("Starting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /asciilogo.txt HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
}

void loop() {

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true) {
      delay(100);
    }
  }
}
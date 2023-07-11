
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

#define D4 2
#ifndef STASSID
#define STASSID "ssid"
#define STAPSK  "pass"
#endif

const char* ssid = STASSID;
const char* pass = STAPSK;
const char* http_username = "admin";
const char* http_password = "admin";
const char* print_this = "<h1>Print that</h1>";

AsyncWebServer server(80);

void setup() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW); // On at first (When D4-> Low, A0 left->ON)

  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", "<html><body><button onclick=\"toggleLed()\">Toggle LED</button><script>function toggleLed(){var xhr = new XMLHttpRequest();xhr.open('GET', '/toggle', true);xhr.send();}</script></body></html>");
  });

  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest* request) {
    digitalWrite(D4, !digitalRead(D4));
    request->send(200, "text/plain", "LED state changed");
  });

  // Start server
  server.begin();
  Serial.print("HTTP server started at ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("The device is disconnected. Server is down xd");
  }
}

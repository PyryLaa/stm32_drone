#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ESP8266WiFiType.h>
#include <string.h>

#ifndef APSSID
#define APSSID "DroneESP"
#define APPSK "eeppinendrone"
#endif

#define MAC_LENGTH 6
// Credentials
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);
WiFiEventHandler connectHandler;
WiFiEventHandler disconnectHandler;
uint8_t connectedDeviceMac[MAC_LENGTH];
bool deviceConnected = false;

enum class Colors : int{
  RED = 0,
  BLUE,
  GREEN,
  ORANGE
};

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP8266 Color Input</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
        input { padding: 10px; font-size: 16px; }
        button { padding: 10px 20px; font-size: 16px; margin-left: 10px; cursor: pointer; }
    </style>
</head>
<body>
    <h2>Enter a Color (red, blue, green, orange)</h2>
    <input type="text" id="colorInput" placeholder="Type a color">
    <button onclick="sendColor()">Submit</button>

    <script>
        function sendColor() {
            let color = document.getElementById('colorInput').value.toLowerCase();
            if (['red', 'blue', 'green', 'orange'].includes(color)) {
                fetch('/led?value=' + color)
                    .then(response => response.text())
                    .then(data => alert(data))
                    .catch(error => console.error('Error:', error));
            } else {
                alert('Invalid color! Please enter red, blue, green, or orange.');
            }
        }
    </script>
</body>
</html>
)rawliteral";

void sendValStm(char* val){
    Serial.print(val);
}


void printMac(const uint8_t *mac) {
  for (int i = 0; i < MAC_LENGTH; i++) {
    Serial.printf("%02X", mac[i]);
    if (i < 5) Serial.print(":");
  }
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected& event){
  Serial.println("Device connected with mac: ");
  printMac(event.mac);
  if(!deviceConnected){
    deviceConnected = true;
    memcpy(connectedDeviceMac, event.mac, MAC_LENGTH);
  }
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& event){
  Serial.println("Device disconnect with mac: ");
  printMac(event.mac);
  if(memcmp(event.mac, connectedDeviceMac, MAC_LENGTH) == 0){
    char buf[] = "{100}";
    sendValStm(buf);
    deviceConnected = false;
    memset(connectedDeviceMac, 0, MAC_LENGTH);
  }
}

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleValue() {
  if(server.hasArg("plain")){
    JsonDocument j_req;
    deserializeJson(j_req, server.arg("plain"));
    char buf[64];
    int val = j_req["value"].as<int>();
    if(100 <= val <= 200){
      sprintf(buf, "{%d}", val);
      sendValStm(buf);
    }
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  connectHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
  disconnectHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/led", HTTP_POST,handleValue);
  server.begin();
}

void loop() {
  server.handleClient();
}

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
    char buf[] = "{0}";
    sendValStm(buf);
    deviceConnected = false;
    memset(connectedDeviceMac, 0, MAC_LENGTH);
  }
}

void handleValue() {
  if(server.hasArg("plain")){
    JsonDocument j_req;
    deserializeJson(j_req, server.arg("plain"));
    char buf[64];
    int val = j_req["value"].as<int>();
    if(val <= 100){
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
  server.on("/led", HTTP_POST,handleValue);
  server.begin();
}

void loop() {
  server.handleClient();
}

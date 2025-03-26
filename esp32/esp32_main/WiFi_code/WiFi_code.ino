#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#ifndef APSSID
#define APSSID "DroneESP"
#define APPSK "eeppinendrone"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

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

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", htmlPage);
  if(server.hasArg("value")){
    //Serial.print(server.arg("value"));
  }
}

void handleColor() {
  if(server.hasArg("plain")){
    JsonDocument j_req;
    deserializeJson(j_req, server.arg("plain"));
    char buf[64];
    sprintf(buf, "{%d}", j_req["value"].as<int>());
    
    Serial.print(buf);
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/led", HTTP_POST,handleColor);
  server.begin();
}

void loop() {
  server.handleClient();
}

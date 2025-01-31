#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "DroneESP"
#define APPSK "eeppinendrone"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

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
}

void handleColor() {
  if (server.hasArg("value")) {
      String color = server.arg("value");
      Serial.print("{" + color + "}");
      server.send(200, "text/plain", "Color received: " + color);
  } else {
      server.send(400, "text/plain", "Invalid request");
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/led", handleColor);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

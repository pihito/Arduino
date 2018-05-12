#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>

 
const char* ssid     = "Livebox-9e38";
const char* password = "EDE79F89D642E0117543DD28A6";

//const char* ssid     = "DARKSIDE";
//const char* password = "8353481dd463";
 
ESP8266WebServer server(80);

String webString="";     // String to display
 
void handle_root() {
  server.send(200, "text/plain", "Hello from esp8266");
  delay(100);
}
 
void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
  Serial.println("------------------------------------------------");
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  //server.on("/", handle_root);
  
  //server.begin();
  //Serial.println("HTTP server started");
}
 
void loop(void)
{
  //server.handleClient();
} 


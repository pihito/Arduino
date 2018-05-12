#include <PubSubClient.h>

#include <ESP8266WiFi.h>

#include <DHT.h>



#define DHTTYPE DHT22
#define DHTPIN  2

//const char* ssid     = "Livebox-9e38";
//const char* password = "EDE79F89D642E0117543DD28A6";

//const char* ssid     = "Mutualab Coworking 1";
//const char* password = "maintenantautravail";

//const char* ssid     = "DARKSIDE";
//const char* password = "8353481dd463";

const char* ssid     = "MY_SENSOR_NETWORK";
const char* password = "12345678";

 
// server address:
IPAddress mqttServer(192, 168, 20, 1);

WiFiClient wclient;
PubSubClient mqttClient(mqttServer,1883,wclient);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

float humidity, temp_f;
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000; 
DHT dht(DHTPIN, DHTTYPE,11);

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  dht.begin();
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



/*void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 5000)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET / HTTP/1.1");
    client.println("Host: 192.168.61.1");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}*/

void gettemperature() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    previousMillis = currentMillis;   
 
    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature(false);     // Read temperature as Fahrenheit
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  /*while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }*/
  delay(5000);
    //httpRequest();
    gettemperature();
    Serial.print("t : ");
    Serial.println(temp_f);
    Serial.print("H : ");
    Serial.println(humidity);
    mqttClient.connect("ESP1");
    char temp_c[20];
    char hum_c[20];
    dtostrf(temp_f,7, 2, temp_c);
    dtostrf(humidity,7, 2, hum_c);
    String jsonStr = "{ \"tmp\": ";
    jsonStr.concat(temp_c);
    jsonStr.concat(",\"hum\":");
    jsonStr.concat(hum_c);
    jsonStr.concat("}");
    mqttClient.publish("SebHome/HugoRoom",jsonStr.c_str());           
}

